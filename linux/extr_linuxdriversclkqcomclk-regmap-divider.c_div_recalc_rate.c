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
struct clk_regmap {int /*<<< orphan*/  regmap; } ;
struct clk_regmap_div {int shift; int /*<<< orphan*/  width; int /*<<< orphan*/  reg; struct clk_regmap clkr; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLK_DIVIDER_ROUND_CLOSEST ; 
 unsigned long divider_recalc_rate (struct clk_hw*,unsigned long,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct clk_regmap_div* to_clk_regmap_div (struct clk_hw*) ; 

__attribute__((used)) static unsigned long div_recalc_rate(struct clk_hw *hw,
				     unsigned long parent_rate)
{
	struct clk_regmap_div *divider = to_clk_regmap_div(hw);
	struct clk_regmap *clkr = &divider->clkr;
	u32 div;

	regmap_read(clkr->regmap, divider->reg, &div);
	div >>= divider->shift;
	div &= BIT(divider->width) - 1;

	return divider_recalc_rate(hw, parent_rate, div, NULL,
				   CLK_DIVIDER_ROUND_CLOSEST, divider->width);
}