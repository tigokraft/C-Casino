#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include "headers.h"



//====================================================
//                  ODDS CALCULATOR
//====================================================
unsigned int getRandomNumberInRange(int value) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    
    unsigned int seed = tv.tv_sec ^ tv.tv_usec ^ getpid();
    
    srand(seed);
    
    return (rand() % 100) + 1;
}

float getRandomFloat(float min, float max) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    
    unsigned int seed = tv.tv_sec ^ tv.tv_usec ^ getpid();
    
    srand(seed);

    return min + ((float)rand() / (float)RAND_MAX) * (max - min);
}

void odds() {
    unsigned int randomNumber = getRandomNumberInRange(100);
    float randomFloat = getRandomFloat(2.0, 3.0);

    if (randomNumber <= 5) {
        randomFloat = 0.0;
    }
    else if(randomNumber >= 6 && randomNumber <= 20) {
        randomFloat = getRandomFloat(1.01, 1.3);
    }
    else if(randomNumber >= 21 && randomNumber <= 35) {
        randomFloat = getRandomFloat(1.3, 1.9);
    }
    else if(randomNumber >= 36 && randomNumber <= 50) {
        randomFloat = getRandomFloat(1.9, 2.3);
    }
    else if(randomNumber >= 51 && randomNumber <= 60) {
        randomFloat = getRandomFloat(2.3, 3.0);
    }
    else if(randomNumber >= 61 && randomNumber <= 70) {
        randomFloat = getRandomFloat(3.0, 3.7);
    }
    else if(randomNumber >= 71 && randomNumber <= 80) {
        randomFloat = getRandomFloat(3.7, 5.0);
    }
    else if(randomNumber >= 81 && randomNumber <= 85) {
        randomFloat = getRandomFloat(5.0, 9.5);
    }
    else if(randomNumber >= 86 && randomNumber <=90 ) {
        randomFloat = getRandomFloat(9.5, 12.5);
    }
    else if (randomNumber >= 91 && randomNumber <= 95) {
        randomFloat = getRandomFloat(12.5, 15.5);
    }
    else if (randomFloat >= 96 && randomNumber <= 99) {
        randomFloat = getRandomFloat(15.5, 19.9);
    }
    else if(randomFloat >= 100) {
        randomFloat = getRandomFloat(19.9, 50);
    }




    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    int consoleWidth = w.ws_col;
    int leadingSpaces = (consoleWidth / 2);
    
    char* spaces = (char*)malloc(leadingSpaces + 1); // Allocate memory for leading spaces
    memset(spaces, ' ', leadingSpaces);
    spaces[leadingSpaces] = '\0';
    
    for (int i = 0; i < (w.ws_row / 2) -1; i++) {
        printf("\n");
    }

    printf("%s%.2f\n",spaces, randomFloat);
}



//====================================================
//                      MENU
//====================================================
char* center() {
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    int consoleWidth = w.ws_col;

    int leadingSpaces = consoleWidth / 2;

    char* spaces = (char*)malloc(leadingSpaces + 1); // Allocate memory for leading spaces
    memset(spaces, ' ', leadingSpaces);
    spaces[leadingSpaces] = '\0';

    return spaces;
}

void hCenter() {
    struct winsize size;
    
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == -1) {
        perror("ioctl");
    }

    for (int i = 0; i < (size.ws_row /2) -1; i++) {
        printf("\n");
    }
}

void start() {
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    int consoleWidth = w.ws_col;
    char starting[] = "STARTING THE GAME\n";
    int textw = strlen(starting);

    int leadingSpaces = ((consoleWidth - textw) / 2);
    char* spaces = (char*)malloc(leadingSpaces + 1); // Allocate memory for leading spaces
    memset(spaces, ' ', leadingSpaces);
    spaces[leadingSpaces] = '\0';

    printf("%s %s\n", spaces, starting);
}

void countdown(int countdown) {
    char* leadingSpaces = center();

    while (countdown >= 0) {
        if (countdown < 10) {
            printf("\r%s0%d",leadingSpaces, countdown); // Updated format string to include space
        } else {
            printf("\r%s%d",leadingSpaces, countdown); // Updated format string to include space
        }
        fflush(stdout); // Flush the output buffer
        sleep(1);
        countdown--;
    }

    system("clear");
}




//====================================================
//                  MAIN GAME
//====================================================


void crash() {
    system("clear");

    hCenter();
    start();
    countdown(5);

    odds();
}
