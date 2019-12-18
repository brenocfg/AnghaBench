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
struct SiS_Private {int /*<<< orphan*/  SiS_P3c2; TYPE_1__* SiS_StandTable; } ;
struct TYPE_2__ {unsigned char MISC; } ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_SetRegByte (struct SiS_Private*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void
SiS_SetMiscRegs(struct SiS_Private *SiS_Pr, unsigned short StandTableIndex)
{
	unsigned char Miscdata = SiS_Pr->SiS_StandTable[StandTableIndex].MISC;

	SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3c2, Miscdata);
}