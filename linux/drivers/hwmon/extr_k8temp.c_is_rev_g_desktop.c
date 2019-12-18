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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int cpuid_ebx (int) ; 

__attribute__((used)) static int is_rev_g_desktop(u8 model)
{
	u32 brandidx;

	if (model < 0x69)
		return 0;

	if (model == 0xc1 || model == 0x6c || model == 0x7c)
		return 0;

	/*
	 * Differentiate between AM2 and ASB1.
	 * See "Constructing the processor Name String" in "Revision
	 * Guide for AMD NPT Family 0Fh Processors" (33610).
	 */
	brandidx = cpuid_ebx(0x80000001);
	brandidx = (brandidx >> 9) & 0x1f;

	/* Single core */
	if ((model == 0x6f || model == 0x7f) &&
	    (brandidx == 0x7 || brandidx == 0x9 || brandidx == 0xc))
		return 0;

	/* Dual core */
	if (model == 0x6b &&
	    (brandidx == 0xb || brandidx == 0xc))
		return 0;

	return 1;
}