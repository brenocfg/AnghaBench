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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  __FPU_FPSCR ; 

int
mffs(u32 *frD)
{
	frD[1] = __FPU_FPSCR;

#ifdef DEBUG
	printk("%s: frD %p: %08x.%08x\n", __func__, frD, frD[0], frD[1]);
#endif

	return 0;
}