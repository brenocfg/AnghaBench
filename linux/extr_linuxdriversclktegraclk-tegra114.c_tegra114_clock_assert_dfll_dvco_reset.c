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
 int DVFS_DFLL_RESET_SHIFT ; 
 scalar_t__ RST_DFLL_DVCO ; 
 scalar_t__ clk_base ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  tegra114_car_barrier () ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

void tegra114_clock_assert_dfll_dvco_reset(void)
{
	u32 v;

	v = readl_relaxed(clk_base + RST_DFLL_DVCO);
	v |= (1 << DVFS_DFLL_RESET_SHIFT);
	writel_relaxed(v, clk_base + RST_DFLL_DVCO);
	tegra114_car_barrier();
}