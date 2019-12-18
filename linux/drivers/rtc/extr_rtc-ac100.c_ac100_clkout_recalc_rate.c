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
struct ac100_clkout {int /*<<< orphan*/  offset; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int AC100_CLKOUT_DIV_SHIFT ; 
 int AC100_CLKOUT_DIV_WIDTH ; 
 unsigned int AC100_CLKOUT_PRE_DIV_SHIFT ; 
 int AC100_CLKOUT_PRE_DIV_WIDTH ; 
 unsigned long AC100_RTC_32K_RATE ; 
 int BIT (int) ; 
 int /*<<< orphan*/  CLK_DIVIDER_POWER_OF_TWO ; 
 int /*<<< orphan*/ * ac100_clkout_prediv ; 
 unsigned long divider_recalc_rate (struct clk_hw*,unsigned long,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct ac100_clkout* to_ac100_clkout (struct clk_hw*) ; 

__attribute__((used)) static unsigned long ac100_clkout_recalc_rate(struct clk_hw *hw,
					      unsigned long prate)
{
	struct ac100_clkout *clk = to_ac100_clkout(hw);
	unsigned int reg, div;

	regmap_read(clk->regmap, clk->offset, &reg);

	/* Handle pre-divider first */
	if (prate != AC100_RTC_32K_RATE) {
		div = (reg >> AC100_CLKOUT_PRE_DIV_SHIFT) &
			((1 << AC100_CLKOUT_PRE_DIV_WIDTH) - 1);
		prate = divider_recalc_rate(hw, prate, div,
					    ac100_clkout_prediv, 0,
					    AC100_CLKOUT_PRE_DIV_WIDTH);
	}

	div = (reg >> AC100_CLKOUT_DIV_SHIFT) &
		(BIT(AC100_CLKOUT_DIV_WIDTH) - 1);
	return divider_recalc_rate(hw, prate, div, NULL,
				   CLK_DIVIDER_POWER_OF_TWO,
				   AC100_CLKOUT_DIV_WIDTH);
}