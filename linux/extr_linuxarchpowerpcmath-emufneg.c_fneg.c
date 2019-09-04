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

int
fneg(u32 *frD, u32 *frB)
{
	frD[0] = frB[0] ^ 0x80000000;
	frD[1] = frB[1];

#ifdef DEBUG
	printk("%s: D %p, B %p: ", __func__, frD, frB);
	dump_double(frD);
	printk("\n");
#endif

	return 0;
}