/**********************************************************************************************************************
File: user_app1.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app1.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp1Initialize(void)
{
 LCDCommand(LCD_CLEAR_CMD);
  LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN);
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_StateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_Error;
  }

} /* end UserApp1Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp1RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp1RunActiveState(void)
{
  UserApp1_StateMachine();

} /* end UserApp1RunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{
static u8 u8ColorIndex = 0;
  static u16 u16BlinkCount = 0;
  static u8 u8Counter = 17;
  static u8 u8Number = 0;
  static u8 u8NumberButton0 = 0;
  static u8 UserApp_au8MyName1[] = "IceCream is coming";
  static u8 UserApp_au8MyName2[] = " Y(ovo)Y ";
  static u8 UserApp_au8MyName3[] = "Ice Cream has sold";
  static u8 UserApp_au8MyName4[] = "Thank you ";
  

  u16BlinkCount++;
  if(u16BlinkCount == 100)
  {
    u16BlinkCount = 0;

    /* Update the counter and roll at 16 */
    u8Counter--;
    if(u8Counter == 0)
    {
      u8Counter = 17;
      
      /* Manage the back light color */
      u8ColorIndex++;
      if(u8ColorIndex == 8)
      {
        u8ColorIndex = 0;
      }

    if( WasButtonPressed(BUTTON1) )
    {
      /* Set the backlight color: white (all), 
      purple (blue + red), blue, cyan (blue + green), 
      green, yellow (green + red), red */
      switch(u8ColorIndex)
      {
        case 1: /* white */
          LedOn(LCD_RED);
          LedOn(LCD_GREEN);
          LedOn(LCD_BLUE);
          break;

        case 2: /* purple */
          LedOn(LCD_RED);
          LedOff(LCD_GREEN);
          LedOn(LCD_BLUE);
          break;
          
        case 3: /* blue */
          LedOff(LCD_RED);
          LedOff(LCD_GREEN);
          LedOn(LCD_BLUE);
          break;
          
        case 4: /* cyan */
          LedOff(LCD_RED);
          LedOn(LCD_GREEN);
          LedOn(LCD_BLUE);
          break;
          
        case 5: /* green */
          LedOff(LCD_RED);
          LedOn(LCD_GREEN);
          LedOff(LCD_BLUE);
          break;
          
        case 6: /* yellow */
          LedOn(LCD_RED);
          LedOn(LCD_GREEN);
          LedOff(LCD_BLUE);
          break;
          
        case 7: /* red */
          LedOn(LCD_RED);
          LedOff(LCD_GREEN);
          LedOff(LCD_BLUE);
          break;
          
        default: /* off */
          LedOff(LCD_RED);
          LedOff(LCD_GREEN);
          LedOff(LCD_BLUE);
          break;
      } /* end switch */
    }
    } /* end if(u8Counter == 16) */
      } /* end if(u16BlinkCount == 500) */
       
  if( WasButtonPressed(BUTTON2))
  {
  /* Parse the current count to set the LEDs.  
      RED is bit 0, ORANGE is bit 1, 
      YELLOW is bit 2, GREEN is bit 3. */
       static u16 u16BlinkCount=0;
 static u8 u8Counter=0;
  u16BlinkCount++;
  if(u8Counter == 14)
 {
 u8Counter =14;
 }
 if(u16BlinkCount == 500)
 { u16BlinkCount = 0; 
  if(u8Counter==1)
 {
 LedOn(RED);
 }
 else
 {
 LedOff(RED);
 }
 if(u8Counter==2)
 {
 LedOn(ORANGE);
 LedOff(RED);
 }
 else
 {
 LedOff(ORANGE);
 }
 if(u8Counter==3)
 {
 LedOn(YELLOW);
 LedOff(ORANGE);
 }
 else
 {
 LedOff(YELLOW);
 }
 if(u8Counter==4)
 {
 LedOn(GREEN);
 LedOff(YELLOW);
 }
 else
 {
 LedOff(GREEN);
 }
 if(u8Counter==5)
 {
 LedOn(CYAN);
 LedOff(GREEN);
 }
 else
 {
 LedOff(CYAN);
 }
if(u8Counter==6)
 {
 LedOn(BLUE);
 LedOff(CYAN);
 }
 else
 {
 LedOff(BLUE);
 }  
 if(u8Counter==7)
 {
 LedOn(PURPLE);
 LedOff(BLUE);
 }
 else
 {
 LedOff(PURPLE);
 } 
 if(u8Counter==8)
 {
 LedOn(BLUE);
 LedOff(CYAN);
 }
  if(u8Counter==9)
 {
 LedOn(CYAN);
 LedOff(PURPLE);
 }
  if(u8Counter==10)
 {
 LedOn(GREEN);
 LedOff(CYAN);
 }
   if(u8Counter==11)
 {
 LedOn(YELLOW);
 LedOff(GREEN);
 }
 if(u8Counter==12)
 {
 LedOn(ORANGE);
 LedOff(YELLOW);
 }
  if(u8Counter==13)
 {
 LedOn(RED);
 LedOff(ORANGE);
 }
  if(u8Counter==14)
  {
       LedOn(WHITE);
       LedOff(PURPLE);
       LedOff(BLUE);
       LedOff(CYAN);
       LedOff(GREEN);
       LedOff(YELLOW);
       LedOff(ORANGE);
       LedOff(RED);
  }
 u8Counter++;
  }
  }
  
     if( WasButtonPressed(BUTTON3))
     {
     ButtonAcknowledge(BUTTON3);
     LCDMessage(LINE1_START_ADDR, UserApp_au8MyName1);
     LCDMessage(LINE2_START_ADDR, UserApp_au8MyName2);
     u8Number++;
       if(u8Number == 2)
       {
         LCDMessage(LINE1_START_ADDR, UserApp_au8MyName3);
         LCDMessage(LINE2_START_ADDR, UserApp_au8MyName4);
          u8Number = 0;
       }
     }
   if( WasButtonPressed(BUTTON0))
  {
  static u16 au16NotesRight[]= {F5, F5, F5, F5, F5, E5, D5, E5, F5, G5, A5, A5, A5, A5, A5, G5, F5, G5, A5, 
A5S, C6, F5, F5, D6, C6, A5S, A5, G5, F5, NO, NO};
  static u16 au16DurationRight[] = {QN, QN, HN, EN, EN, EN, EN, EN, EN, QN, QN, QN, HN, EN, EN, EN, EN, EN, EN, 
QN, HN, HN, EN, EN, EN, EN, QN, QN, HN, HN, FN};
  static u16 au16NoteTypeRight[] = {RT, RT, HT, RT, RT, RT, RT, RT, RT, RT, RT, RT, HT, RT, RT, RT, RT, RT, RT, 
RT, RT, HT, RT, RT, RT, RT, RT, RT, RT, HT, HT};
  static u8 u8IndexRight = 0;
  static u32 u32RightTimer = 0;
  static u16 u16CurrentDurationRight = 0;
  static u16 u16NoteSilentDurationRight = 0;
  static bool bNoteActiveNextRight = TRUE;

  u8 u8CurrentIndex;
  if(IsTimeUp(&u32RightTimer, (u32)u16CurrentDurationRight))
  {
    u32RightTimer = G_u32SystemTime1ms;
    u8CurrentIndex = u8IndexRight;
    
    /* Set up to play current note */
    if(bNoteActiveNextRight)
    {
      if(au16NoteTypeRight[u8CurrentIndex] == RT)
      {
        u16CurrentDurationRight = au16DurationRight[u8CurrentIndex] - REGULAR_NOTE_ADJUSTMENT;
        u16NoteSilentDurationRight = REGULAR_NOTE_ADJUSTMENT;
        bNoteActiveNextRight = FALSE;
      } /* end RT case */
    
      else if(au16NoteTypeRight[u8CurrentIndex] == ST)
      {
        u16CurrentDurationRight = STACCATO_NOTE_TIME;
        u16NoteSilentDurationRight = au16DurationRight[u8CurrentIndex] - STACCATO_NOTE_TIME;
        bNoteActiveNextRight = FALSE;
      } /* end ST case */

      else if(au16NoteTypeRight[u8CurrentIndex] == HT)
      {
        u16CurrentDurationRight = au16DurationRight[u8CurrentIndex];
        u16NoteSilentDurationRight = 0;
        bNoteActiveNextRight = TRUE;

        u8IndexRight++;
        if(u8IndexRight == sizeof(au16NotesRight) / sizeof(u16) )
        {
          u8IndexRight = 0;
        }
      } /* end HT case */

      /* Set the buzzer frequency for the note (handle NO special case) */
      if(au16NotesRight[u8CurrentIndex] != NO)
      {
        PWMAudioSetFrequency(BUZZER1, au16NotesRight[u8CurrentIndex]);
        PWMAudioOn(BUZZER1);
      }
      else
      {                
        PWMAudioOff(BUZZER1);
      }
    } /* end if(bNoteActiveNextRight) */
    else
    {
      /* No active note */
      PWMAudioOff(BUZZER1);
      u32RightTimer = G_u32SystemTime1ms;
      u16CurrentDurationRight = u16NoteSilentDurationRight;
      bNoteActiveNextRight = TRUE;
 
      u8IndexRight++;
      if(u8IndexRight == sizeof(au16NotesRight) / sizeof(u16) )
      {
        u8IndexRight = 0;
      }
    } /* end else if(bNoteActiveNextRight) */
  } /* end if(IsTimeUp(&u32RightTimer, (u32)u16CurrentDurationRight)) */
  static u16 au16NotesLeft[]  = {NO,NO,A4,E5,A5,G4,E5,G5,F4,C5,F5,E4,B4,E5,D4,A4,D5,C4,G4,C5,D4,B4,D5,E4,B4,E5,G5,A4,E5,A5,E5,G4,E5,A5,E5,F4,C5,F5,C5,E4,C5,F5,C5,D4,A4,D5,A4,C4,G4,C5,G4,D4,B4,D5,F5,E4,C4,E4,G5,A4,E5,B5,C6,A4,B5,G4,G5,C5,G5,C6,E6,G6,E6,C6,G5,G4,D5,A5,D6,B5,G5,D5,F4,C5,F5,A5,C6,A5,F5,C5,E4,B4,E5,G5,B5,D6,G6,B6,A4,E5,A5,C6,E6,C6,A5,E5,G4,D5,G5,B5,D6,B5,G5,D5};
  static u16 au16DurationLeft[] = {QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN};
  static u16 au16NoteTypeLeft[] = {HT,HT,RT,RT,HT,RT,RT,HT,RT,RT,HT,RT,RT,HT,RT,RT,HT,RT,RT,HT,RT,RT,HT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,RT,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST,ST};
  static u8 u8IndexLeft = 0;
  static u32 u32LeftTimer = 0;
  static u16 u16CurrentDurationLeft = 0;
  static u16 u16NoteSilentDurationLeft = 0;
  static bool bNoteActiveNextLeft = TRUE;
  /* Left Hand */
  if(IsTimeUp(&u32LeftTimer, (u32)u16CurrentDurationLeft))
  {
    u32LeftTimer = G_u32SystemTime1ms;
    u8CurrentIndex = u8IndexLeft;
    
    /* Set up to play current note */
    if(bNoteActiveNextLeft)
    {
      if(au16NoteTypeLeft[u8CurrentIndex] == RT)
      {
        u16CurrentDurationLeft = au16DurationLeft[u8CurrentIndex] - REGULAR_NOTE_ADJUSTMENT;
        u16NoteSilentDurationLeft = REGULAR_NOTE_ADJUSTMENT;
        bNoteActiveNextLeft = FALSE;
      }
    
      else if(au16NoteTypeLeft[u8CurrentIndex] == ST)
      {
        u16CurrentDurationLeft = STACCATO_NOTE_TIME;
        u16NoteSilentDurationLeft = au16DurationLeft[u8CurrentIndex] - STACCATO_NOTE_TIME;
        bNoteActiveNextLeft = FALSE;
      }

      else if(au16NoteTypeLeft[u8CurrentIndex] == HT)
      {
        u16CurrentDurationLeft = au16DurationLeft[u8CurrentIndex];
        u16NoteSilentDurationLeft = 0;
        bNoteActiveNextLeft = TRUE;

        u8IndexLeft++;
        if(u8IndexLeft == sizeof(au16NotesLeft) / sizeof(u16) )
        {
          u8IndexLeft = 0;
        }
      }

      /* Set the buzzer frequency for the note (handle NO special case) */
      if(au16NotesLeft[u8CurrentIndex] != NO)
      {
        PWMAudioSetFrequency(BUZZER2, au16NotesLeft[u8CurrentIndex]);
        PWMAudioOn(BUZZER2);
      }
      else
      {                
        PWMAudioOff(BUZZER2);
      }
    }
    else
    {
      PWMAudioOff(BUZZER2);
      u32LeftTimer = G_u32SystemTime1ms;
      u16CurrentDurationLeft = u16NoteSilentDurationLeft;
      bNoteActiveNextLeft = TRUE;
      
      u8IndexLeft++;
      if(u8IndexLeft == sizeof(au16NotesLeft) / sizeof(u16) )
      {
        u8IndexLeft = 0;
      }
    } /* end else if(bNoteActiveNextLeft) */
  }/* end if(IsTimeUp(&u32LeftTimer, (u32)u16CurrentDurationLeft)) */
  }

} /* end UserApp1SM_Idle() */
    

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
