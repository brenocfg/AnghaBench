#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct SiS_Private {unsigned short CModeFlag; TYPE_2__* SiS_EModeIDTable; TYPE_1__* SiS_SModeIDTable; scalar_t__ UseCustomMode; } ;
struct TYPE_4__ {unsigned short Ext_ModeFlag; } ;
struct TYPE_3__ {unsigned short St_ModeFlag; } ;

/* Variables and functions */

unsigned short
SiS_GetModeFlag(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		unsigned short ModeIdIndex)
{
   if(SiS_Pr->UseCustomMode) {
      return SiS_Pr->CModeFlag;
   } else if(ModeNo <= 0x13) {
      return SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
   } else {
      return SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
   }
}