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
struct SiS_Private {unsigned long SiS_P3c4; unsigned long SiS_P3d4; unsigned long SiS_P3c0; unsigned long SiS_P3ce; unsigned long SiS_P3c2; unsigned long SiS_P3ca; unsigned long SiS_P3c6; unsigned long SiS_P3c7; unsigned long SiS_P3c8; unsigned long SiS_P3c9; unsigned long SiS_P3cb; unsigned long SiS_P3cc; unsigned long SiS_P3cd; unsigned long SiS_P3da; scalar_t__ SiS_Part1Port; } ;

/* Variables and functions */
 scalar_t__ SIS_CRT2_PORT_04 ; 

__attribute__((used)) static void SiSUSBRegInit(struct SiS_Private *SiS_Pr, unsigned long BaseAddr)
{
	SiS_Pr->SiS_P3c4 = BaseAddr + 0x14;
	SiS_Pr->SiS_P3d4 = BaseAddr + 0x24;
	SiS_Pr->SiS_P3c0 = BaseAddr + 0x10;
	SiS_Pr->SiS_P3ce = BaseAddr + 0x1e;
	SiS_Pr->SiS_P3c2 = BaseAddr + 0x12;
	SiS_Pr->SiS_P3ca = BaseAddr + 0x1a;
	SiS_Pr->SiS_P3c6 = BaseAddr + 0x16;
	SiS_Pr->SiS_P3c7 = BaseAddr + 0x17;
	SiS_Pr->SiS_P3c8 = BaseAddr + 0x18;
	SiS_Pr->SiS_P3c9 = BaseAddr + 0x19;
	SiS_Pr->SiS_P3cb = BaseAddr + 0x1b;
	SiS_Pr->SiS_P3cc = BaseAddr + 0x1c;
	SiS_Pr->SiS_P3cd = BaseAddr + 0x1d;
	SiS_Pr->SiS_P3da = BaseAddr + 0x2a;
	SiS_Pr->SiS_Part1Port = BaseAddr + SIS_CRT2_PORT_04;
}