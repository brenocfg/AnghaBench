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

__attribute__((used)) static unsigned char fsp_test_swap_cmd(unsigned char reg_val)
{
	switch (reg_val) {
	case 10: case 20: case 40: case 60: case 80: case 100: case 200:
		/*
		 * The requested value being sent to FSP matched to possible
		 * sample rates, swap the given value such that the hardware
		 * wouldn't get confused.
		 */
		return (reg_val >> 4) | (reg_val << 4);
	default:
		return reg_val;	/* swap isn't necessary */
	}
}