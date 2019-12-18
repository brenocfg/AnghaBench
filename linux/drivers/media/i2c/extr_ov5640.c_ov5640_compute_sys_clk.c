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
typedef  unsigned long u8 ;
struct ov5640_dev {unsigned long xclk_freq; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long ov5640_compute_sys_clk(struct ov5640_dev *sensor,
					    u8 pll_prediv, u8 pll_mult,
					    u8 sysdiv)
{
	unsigned long sysclk = sensor->xclk_freq / pll_prediv * pll_mult;

	/* PLL1 output cannot exceed 1GHz. */
	if (sysclk / 1000000 > 1000)
		return 0;

	return sysclk / sysdiv;
}