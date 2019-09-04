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

/* Variables and functions */
 int __FPU_FPSCR ; 

int
mtfsb0(int crbD)
{
	if ((crbD != 1) && (crbD != 2))
		__FPU_FPSCR &= ~(1 << (31 - crbD));

#ifdef DEBUG
	printk("%s: %d %08lx\n", __func__, crbD, __FPU_FPSCR);
#endif

	return 0;
}