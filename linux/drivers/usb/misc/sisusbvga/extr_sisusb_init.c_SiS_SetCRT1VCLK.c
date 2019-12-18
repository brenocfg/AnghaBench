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
struct SiS_Private {int /*<<< orphan*/  SiS_P3c4; TYPE_2__* SiS_VCLKData; TYPE_1__* SiS_RefIndex; } ;
struct TYPE_4__ {unsigned short SR2B; unsigned short SR2C; } ;
struct TYPE_3__ {unsigned short Ext_CRTVCLK; } ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_SetReg (struct SiS_Private*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegAND (struct SiS_Private*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
SiS_SetCRT1VCLK(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		unsigned short rrti)
{
	unsigned short index = SiS_Pr->SiS_RefIndex[rrti].Ext_CRTVCLK;
	unsigned short clka = SiS_Pr->SiS_VCLKData[index].SR2B;
	unsigned short clkb = SiS_Pr->SiS_VCLKData[index].SR2C;

	SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3c4, 0x31, 0xCF);

	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x2B, clka);
	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x2C, clkb);
	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x2D, 0x01);
}