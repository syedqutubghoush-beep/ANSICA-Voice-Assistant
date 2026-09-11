#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define Printf(...) printf(__VA_ARGS__)

void speak(const char *text)
{
    char command[1000];

    /*
       PowerShell uses Windows' built-in
       System.Speech text-to-speech system.
    */

    snprintf(command, sizeof(command),
        "powershell -Command \"Add-Type -AssemblyName System.Speech; "
        "$speak = New-Object System.Speech.Synthesis.SpeechSynthesizer; "
        "$speak.Speak(\\\"%s\\\")",
        text);

    system(command);
}


void listen()
{
    /*
       Windows Speech Recognition is opened here.

       Press Windows + H and speak your command.
       Windows converts your speech into text.
    */

    printf("\n");
    printf("====================================\n");
    printf("🎤 Speak your command using Windows Voice Typing\n");
    printf("====================================\n");
    printf("Press ENTER to activate Windows voice input...\n");

    getchar();

    system("start ms-settings:privacy-microphone");
}


void getTime()
{
    time_t currentTime;
    struct tm *localTime;

    currentTime = time(NULL);
    localTime = localtime(&currentTime);

    printf("ANSICA: Current time is %02d:%02d:%02d\n",
           localTime->tm_hour,
           localTime->tm_min,
           localTime->tm_sec);
}


void getDate()
{
    time_t currentTime;
    struct tm *localTime;

    currentTime = time(NULL);
    localTime = localtime(&currentTime);

    printf("ANSICA: Today's date is %02d/%02d/%04d\n",
           localTime->tm_mday,
           localTime->tm_mon + 1,
           localTime->tm_year + 1900);
}


void processCommand(char command[])
{
    /*
       Convert command to lowercase.
    */

    for (int i = 0; command[i] != '\0'; i++)
    {
        command[i] = (char)tolower((unsigned char)command[i]);
    }


    if (strstr(command, "hello") != NULL ||
        strstr(command, "hi") != NULL)
    {
        printf("ANSICA: Hello! Nice to meet you.\n");
        speak("Hello! Nice to meet you.");
    }


    else if (strstr(command, "your name") != NULL)
    {
        printf("ANSICA: My name is ANSICA and it stands for Artificial Neural Network System Interactive Compute Assistant.\n");
        speak("My name is ANSICA and it stands for Artificial Neural Network System Interactive Compute Assistant.");
    }


    else if (strstr(command, "time") != NULL)
    {
        getTime();

        speak("The current time is available on the screen.");
    }


    else if (strstr(command, "date") != NULL ||
             strstr(command, "today") != NULL)
    {
        getDate();

        speak("Todays date is displayed on the screen.");
    }


    else if (strstr(command, "google") != NULL ||
             strstr(command, "browser") != NULL)
    {
        printf("ANSICA: Opening Google...\n");

        speak("Opening Google.");

        system("start \"\" \"C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe\"");
    }

    else if (strstr(command, "notepad") != NULL)
    {
        printf("ANSICA: Opening Notepad...\n");

        speak("Opening Notepad.");

        system("start \"\" \"C:\\Windows\\System32\\notepad.exe\"");
    }

    else if (strstr(command, "calculator") != NULL)
    {
        printf("ANSICA: Opening Calculator...\n");

        speak("Opening Calculator.");

        system("start \"\" \"C:\\Windows\\System32\\calc.exe\"");
    }

    else if (strstr(command, "youtube") != NULL)
    {
        printf("ANSICA: Opening YouTube...\n");

        speak("Opening YouTube.");

        system("start https://www.youtube.com/");
    }

    else if (strstr(command, "help") != NULL)
    {
        printf("\n");
        printf("========== COMMANDS ==========\n");
        printf("hello\n");
        printf("your name\n");
        printf("time\n");
        printf("date\n");
        printf("google\n");
        printf("notepad\n");
        printf("calculator\n");
        printf("youtube\n");
        printf("help\n");
        printf("exit\n");
        printf("==============================\n");

        speak("I have displayed the available commands.");
    }


    else if (strstr(command, "exit") != NULL ||
             strstr(command, "goodbye") != NULL)
    {
        printf("ANSICA: Goodbye!\n");

        speak("Goodbye!");

        exit(0);
    }


    else
    {
        printf("ANSICA: I do not understand that command.\n");

        speak("Sorry, I do not understand that command.");
    }
}


int main()
{
    char command[500];

    printf("\n");
    printf("========================================\n");
    printf("       🤖 C WINDOWS VOICE ANSICA\n");
    printf("========================================\n");

    printf("\n");
    printf("ANSICA: System started.\n");

    speak("Hello! I am your C voice ANSICA.");

    printf("\n");
    printf("For now, enter what you said after Windows\n");
    printf("recognizes your voice.\n");

    printf("\n");
    printf("Example commands:\n");
    printf("  hello\n");
    printf("  what is your name\n");
    printf("  tell me the time\n");
    printf("  tell me today's date\n");
    printf("  open google\n");
    printf("  open notepad\n");
    printf("  open calculator\n");
    printf("  open youtube\n");
    printf("  help\n");
    printf("  exit\n");


    while (1)
    {
        printf("\nYou: ");

        fgets(command, sizeof(command), stdin);

        command[strcspn(command, "\n")] = '\0';

        processCommand(command);
    }

    return 0;
}
