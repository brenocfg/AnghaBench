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
typedef  scalar_t__ const u32 ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (scalar_t__ const,scalar_t__ const) ; 
 int EINVAL ; 

__attribute__((used)) static int _sunxi_nand_lookup_timing(const s32 *lut, int lut_size, u32 duration,
		u32 clk_period)
{
	u32 clk_cycles = DIV_ROUND_UP(duration, clk_period);
	int i;

	for (i = 0; i < lut_size; i++) {
		if (clk_cycles <= lut[i])
			return i;
	}

	/* Doesn't fit */
	return -EINVAL;
}