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
struct SiS_Private {scalar_t__ ChipType; int /*<<< orphan*/  SiS_Part1Port; } ;

/* Variables and functions */
 scalar_t__ SIS_315H ; 
 unsigned short SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SiS_HaveBridge (struct SiS_Private*) ; 

__attribute__((used)) static bool
SiS_BridgeIsEnabled(struct SiS_Private *SiS_Pr)
{
   unsigned short flag;

   if(SiS_HaveBridge(SiS_Pr)) {
      flag = SiS_GetReg(SiS_Pr->SiS_Part1Port,0x00);
      if(SiS_Pr->ChipType < SIS_315H) {
	flag &= 0xa0;
	if((flag == 0x80) || (flag == 0x20)) return true;
      } else {
	flag &= 0x50;
	if((flag == 0x40) || (flag == 0x10)) return true;
      }
   }
   return false;
}