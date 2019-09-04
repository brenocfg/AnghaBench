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
typedef  int u64 ;
typedef  int u32 ;
struct tegra_clk_frac_div {int shift; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int div_mask (struct tegra_clk_frac_div*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int get_mul (struct tegra_clk_frac_div*) ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 struct tegra_clk_frac_div* to_clk_frac_div (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_frac_div_recalc_rate(struct clk_hw *hw,
					     unsigned long parent_rate)
{
	struct tegra_clk_frac_div *divider = to_clk_frac_div(hw);
	u32 reg;
	int div, mul;
	u64 rate = parent_rate;

	reg = readl_relaxed(divider->reg) >> divider->shift;
	div = reg & div_mask(divider);

	mul = get_mul(divider);
	div += mul;

	rate *= mul;
	rate += div - 1;
	do_div(rate, div);

	return rate;
}