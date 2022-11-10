#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main()
    {
        void sigint_handler(int sig);
        int child;
        int pipefds[2];
        char buffer[50];
        char s[50];

        if (signal(SIGINT, sigint_handler) == SIG_ERR)
        {
            perror("signal SIGINT");
        }

        if(pipe(pipefds) == -1)
        {
            perror("Pipe Error");
            exit(EXIT_FAILURE);
        }

        printf("Please insert your name:");

        if (fgets(s, sizeof(s), stdin) == NULL)
        {
            perror("Input error");
        }
        
        else 
        {
            s[strcspn(s, "\n")] = '\0';
            printf("\nYou entered: %s\n", s);
        }

        printf("\nEnter the amount of looping you want: ");
        scanf("%d", &child);

        
        if (child <= 0)
        {
            perror("Error occured");
        }
        else 
        {
            printf("Chosen amount is: %d\n\n", child);
        }

        write(pipefds[1], &s, sizeof(s));
        read(pipefds[0], &buffer, sizeof(buffer));

        for(int i = 0; i <("%d", child) ; i++) 
        {
            pid_t pid = fork();


                if(pid == 0) 
                {
                    printf("Your name is: '%s'\n", buffer);
                    exit(0);
                }
                
                else 
                {
                    printf("Please wait\n");
                    wait (NULL);
                    close(pipefds[1]);
                    close(pipefds[0]);
                    printf("Done.\n\n");
                }
        }
    }

    void sigint_handler(int sig)
    {
        printf("Process interrupted\n");
        exit(1);
    }
