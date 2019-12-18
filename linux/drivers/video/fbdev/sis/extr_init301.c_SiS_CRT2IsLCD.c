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
struct SiS_Private {scalar_t__ ChipType; int /*<<< orphan*/  SiS_P3d4; int /*<<< orphan*/  SiS_P3c4; } ;

/* Variables and functions */
 scalar_t__ SIS_730 ; 
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
SiS_CRT2IsLCD(struct SiS_Private *SiS_Pr)
{
   if(SiS_Pr->ChipType == SIS_730) {
      if(SiS_GetReg(SiS_Pr->SiS_P3c4,0x13) & 0x20) return true;
   }
   if(SiS_GetReg(SiS_Pr->SiS_P3d4,0x30) & 0x20) return true;
   return false;
}