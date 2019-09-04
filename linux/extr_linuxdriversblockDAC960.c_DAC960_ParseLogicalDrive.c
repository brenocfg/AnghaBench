#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  DAC960_Controller_T ;

/* Variables and functions */
 int DAC960_MaxLogicalDrives ; 
 unsigned long simple_strtoul (char*,char**,int) ; 

__attribute__((used)) static bool DAC960_ParseLogicalDrive(DAC960_Controller_T *Controller,
					char *UserCommandString,
					unsigned char *LogicalDriveNumber)
{
  char *NewUserCommandString = UserCommandString;
  unsigned long XLogicalDriveNumber;
  while (*UserCommandString == ' ') UserCommandString++;
  if (UserCommandString == NewUserCommandString)
    return false;
  XLogicalDriveNumber =
    simple_strtoul(UserCommandString, &NewUserCommandString, 10);
  if (NewUserCommandString == UserCommandString ||
      *NewUserCommandString != '\0' ||
      XLogicalDriveNumber > DAC960_MaxLogicalDrives - 1)
    return false;
  *LogicalDriveNumber = XLogicalDriveNumber;
  return true;
}