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
struct SiS_Private {int /*<<< orphan*/  SiS_P3c4; } ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_SetReg (struct SiS_Private*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegAND (struct SiS_Private*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void SiS_ClearExt1Regs(struct SiS_Private *SiS_Pr, unsigned short ModeNo)
{
	int i;

	for (i = 0x0A; i <= 0x0E; i++) {
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, i, 0x00);
	}

	SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3c4, 0x37, 0xFE);
}