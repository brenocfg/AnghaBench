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
struct clk_hw {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long exynos_cpuclk_recalc_rate(struct clk_hw *hw,
			unsigned long parent_rate)
{
	/*
	 * The CPU clock output (armclk) rate is the same as its parent
	 * rate. Although there exist certain dividers inside the CPU
	 * clock block that could be used to divide the parent clock,
	 * the driver does not make use of them currently, except during
	 * frequency transitions.
	 */
	return parent_rate;
}