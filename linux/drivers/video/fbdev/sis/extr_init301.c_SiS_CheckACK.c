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
struct SiS_Private {unsigned short SiS_DDC_Data; int /*<<< orphan*/  SiS_DDC_Index; int /*<<< orphan*/  SiS_DDC_Port; int /*<<< orphan*/  SiS_DDC_NData; } ;

/* Variables and functions */
 unsigned short SiS_GetReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiS_SetRegANDOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetSCLKHigh (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_SetSCLKLow (struct SiS_Private*) ; 

__attribute__((used)) static unsigned short
SiS_CheckACK(struct SiS_Private *SiS_Pr)
{
  unsigned short tempah;

  SiS_SetSCLKLow(SiS_Pr);				           /* (SC->low) */
  SiS_SetRegANDOR(SiS_Pr->SiS_DDC_Port,
		  SiS_Pr->SiS_DDC_Index,
		  SiS_Pr->SiS_DDC_NData,
		  SiS_Pr->SiS_DDC_Data);			   /* (SD->high) */
  SiS_SetSCLKHigh(SiS_Pr);				           /* SC->high = clock impulse for ack */
  tempah = SiS_GetReg(SiS_Pr->SiS_DDC_Port,SiS_Pr->SiS_DDC_Index); /* Read SD */
  SiS_SetSCLKLow(SiS_Pr);				           /* SC->low = end of clock impulse */
  if(tempah & SiS_Pr->SiS_DDC_Data) return 1;			   /* Ack OK if bit = 0 */
  return 0;
}