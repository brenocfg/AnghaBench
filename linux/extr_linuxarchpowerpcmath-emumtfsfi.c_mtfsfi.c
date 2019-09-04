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
mtfsfi(unsigned int crfD, unsigned int IMM)
{
	u32 mask = 0xf;

	if (!crfD)
		mask = 9;

	__FPU_FPSCR &= ~(mask << ((7 - crfD) << 2));
	__FPU_FPSCR |= (IMM & 0xf) << ((7 - crfD) << 2);

#ifdef DEBUG
	printk("%s: %d %x: %08lx\n", __func__, crfD, IMM, __FPU_FPSCR);
#endif

	return 0;
}