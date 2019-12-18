#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct SiS_Private {scalar_t__ SiS_ModeType; TYPE_1__* SiS_SModeIDTable; } ;
struct TYPE_2__ {unsigned short St_StTableIndex; } ;

/* Variables and functions */
 scalar_t__ ModeEGA ; 

unsigned short
SiS_GetModePtr(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex)
{
   unsigned short index;

   if(ModeNo <= 0x13) {
      index = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_StTableIndex;
   } else {
      if(SiS_Pr->SiS_ModeType <= ModeEGA) index = 0x1B;
      else index = 0x0F;
   }
   return index;
}