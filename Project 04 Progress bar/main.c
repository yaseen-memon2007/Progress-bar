 #include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define BAR_LENGTH 30
#define MAX_TASKS 10

#define COLOR_RESET   7   
#define COLOR_GREEN   10 
#define COLOR_RED     12  
#define COLOR_BLUE    9   
#define COLOR_YELLOW  14  

typedef struct
{
    int id;
    int progress;
    int step;
} Task;

void print_bar(Task task);
void clear_screen();
void set_color(int color);

int main()
{
    Task tasks[MAX_TASKS];
    srand(time(NULL));

    
    for (int i = 0; i < MAX_TASKS; i++)
    {
        tasks[i].id = i + 1;
        tasks[i].progress = 0;
        tasks[i].step = rand() % 5 + 1;   
    }

    time_t start_time = time(NULL);   
    int tasks_incomplete = 1;

    while (tasks_incomplete)
    {
        tasks_incomplete = 0;
        clear_screen();

        
        set_color(COLOR_BLUE);
        printf("=========== Progress Bar ===========\n");
        set_color(COLOR_RESET);

        
        double elapsed = difftime(time(NULL), start_time);
        printf("Elapsed Time: %.0f sec\n\n", elapsed);

        for (int i = 0; i < MAX_TASKS; i++)
        {
            tasks[i].progress += tasks[i].step;
            if (tasks[i].progress > 100)
                tasks[i].progress = 100;
            if (tasks[i].progress < 100)
                tasks_incomplete = 1;
            print_bar(tasks[i]);
        }

        Sleep(1000);
    }

    set_color(COLOR_YELLOW);
    printf("\nAll tasks completed!\n");
    set_color(COLOR_RESET);

    return 0;
}

void print_bar(Task task)
{
    int bars = (task.progress * BAR_LENGTH) / 100;

    printf("Task %2d: [", task.id);

    
    if (task.step <= 2)
        set_color(COLOR_RED);
    else
        set_color(COLOR_GREEN);

    for (int i = 0; i < BAR_LENGTH; i++)
    {
        if (i < bars)
            printf("=");
        else
            printf(" ");
    }

    set_color(COLOR_RESET);
    printf("] %3d%%", task.progress);

    if (task.progress == 100)
    {
        set_color(COLOR_YELLOW);
        printf("  Completed");
        set_color(COLOR_RESET);
    }

    printf("\n");
}

void clear_screen()
{
    system("cls");
}

void set_color(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}