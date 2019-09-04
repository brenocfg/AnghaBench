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
typedef  int /*<<< orphan*/  u64 ;
struct clk_pm_cpu {int /*<<< orphan*/  shift_div; int /*<<< orphan*/  reg_div; int /*<<< orphan*/  nb_pm_base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP_ULL (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int armada_3700_pm_dvfs_get_cpu_div (int /*<<< orphan*/ ) ; 
 scalar_t__ armada_3700_pm_dvfs_is_enabled (int /*<<< orphan*/ ) ; 
 unsigned int get_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_pm_cpu* to_clk_pm_cpu (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_pm_cpu_recalc_rate(struct clk_hw *hw,
					    unsigned long parent_rate)
{
	struct clk_pm_cpu *pm_cpu = to_clk_pm_cpu(hw);
	unsigned int div;

	if (armada_3700_pm_dvfs_is_enabled(pm_cpu->nb_pm_base))
		div = armada_3700_pm_dvfs_get_cpu_div(pm_cpu->nb_pm_base);
	else
		div = get_div(pm_cpu->reg_div, pm_cpu->shift_div);
	return DIV_ROUND_UP_ULL((u64)parent_rate, div);
}