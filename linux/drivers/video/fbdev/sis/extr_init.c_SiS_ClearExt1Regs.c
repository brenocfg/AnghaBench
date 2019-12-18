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
struct SiS_Private {scalar_t__ ChipType; int /*<<< orphan*/  SiS_P3c4; } ;

/* Variables and functions */
 scalar_t__ SIS_315H ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
SiS_ClearExt1Regs(struct SiS_Private *SiS_Pr, unsigned short ModeNo)
{
   unsigned short i;

   for(i = 0x0A; i <= 0x0E; i++) {
      SiS_SetReg(SiS_Pr->SiS_P3c4,i,0x00);
   }

   if(SiS_Pr->ChipType >= SIS_315H) {
      SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x37,0xFE);
      if(ModeNo <= 0x13) {
	 if(ModeNo == 0x06 || ModeNo >= 0x0e) {
	    SiS_SetReg(SiS_Pr->SiS_P3c4,0x0e,0x20);
	 }
      }
   }
}