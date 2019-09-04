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

__attribute__((used)) static bool pll_is_locked(u32 stat)
{
	/*
	 * Required value for each bitfield listed below
	 *
	 * PLL_STATUS[6] = 0  PLL_BYPASS
	 * PLL_STATUS[5] = 0  PLL_HIGHJITTER
	 *
	 * PLL_STATUS[3] = 0  PLL_LOSSREF
	 * PLL_STATUS[2] = 0  PLL_RECAL
	 * PLL_STATUS[1] = 1  PLL_LOCK
	 * PLL_STATUS[0] = 1  PLL_CTRL_RESET_DONE
	 */
	return ((stat & 0x6f) == 0x3);
}