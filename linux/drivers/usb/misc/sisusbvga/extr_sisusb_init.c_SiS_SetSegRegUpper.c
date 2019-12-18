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
struct SiS_Private {int /*<<< orphan*/  SiS_P3cd; int /*<<< orphan*/  SiS_P3cb; } ;

/* Variables and functions */
 int SiS_GetRegByte (struct SiS_Private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiS_SetRegByte (struct SiS_Private*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void SiS_SetSegRegUpper(struct SiS_Private *SiS_Pr, unsigned short value)
{
	unsigned short temp;

	value &= 0x00ff;
	temp = SiS_GetRegByte(SiS_Pr, SiS_Pr->SiS_P3cb) & 0x0f;
	temp |= (value & 0xf0);
	SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3cb, temp);
	temp = SiS_GetRegByte(SiS_Pr, SiS_Pr->SiS_P3cd) & 0x0f;
	temp |= (value << 4);
	SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3cd, temp);
}