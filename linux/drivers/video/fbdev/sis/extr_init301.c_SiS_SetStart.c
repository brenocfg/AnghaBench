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
struct SiS_Private {int SiS_DDC_Data; int /*<<< orphan*/  SiS_DDC_NData; int /*<<< orphan*/  SiS_DDC_Index; int /*<<< orphan*/  SiS_DDC_Port; } ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_SetRegANDOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SiS_SetSCLKHigh (struct SiS_Private*) ; 
 scalar_t__ SiS_SetSCLKLow (struct SiS_Private*) ; 

__attribute__((used)) static unsigned short
SiS_SetStart(struct SiS_Private *SiS_Pr)
{
  if(SiS_SetSCLKLow(SiS_Pr)) return 0xFFFF;			/* (SC->low)  */
  SiS_SetRegANDOR(SiS_Pr->SiS_DDC_Port,
		  SiS_Pr->SiS_DDC_Index,
		  SiS_Pr->SiS_DDC_NData,
		  SiS_Pr->SiS_DDC_Data);        		/* SD->high */
  if(SiS_SetSCLKHigh(SiS_Pr)) return 0xFFFF;			/* SC->high */
  SiS_SetRegANDOR(SiS_Pr->SiS_DDC_Port,
		  SiS_Pr->SiS_DDC_Index,
		  SiS_Pr->SiS_DDC_NData,
		  0x00);					/* SD->low = start condition */
  if(SiS_SetSCLKHigh(SiS_Pr)) return 0xFFFF;			/* (SC->low) */
  return 0;
}