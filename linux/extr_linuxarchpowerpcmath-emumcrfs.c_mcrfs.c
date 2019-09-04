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
typedef  int u32 ;

/* Variables and functions */
 int __FPU_FPSCR ; 

int
mcrfs(u32 *ccr, u32 crfD, u32 crfS)
{
	u32 value, clear;

#ifdef DEBUG
	printk("%s: %p (%08x) %d %d\n", __func__, ccr, *ccr, crfD, crfS);
#endif

	clear = 15 << ((7 - crfS) << 2);
	if (!crfS)
		clear = 0x90000000;

	value = (__FPU_FPSCR >> ((7 - crfS) << 2)) & 15;
	__FPU_FPSCR &= ~(clear);

	*ccr &= ~(15 << ((7 - crfD) << 2));
	*ccr |= (value << ((7 - crfD) << 2));

#ifdef DEBUG
	printk("CR: %08x\n", __func__, *ccr);
#endif

	return 0;
}