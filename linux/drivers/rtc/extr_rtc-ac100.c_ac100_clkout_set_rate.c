#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clk_hw {int dummy; } ;
struct ac100_clkout {int /*<<< orphan*/  offset; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {unsigned long div; int val; } ;

/* Variables and functions */
 int AC100_CLKOUT_DIV_SHIFT ; 
 int AC100_CLKOUT_DIV_WIDTH ; 
 int AC100_CLKOUT_PRE_DIV_SHIFT ; 
 int AC100_CLKOUT_PRE_DIV_WIDTH ; 
 unsigned long AC100_RTC_32K_RATE ; 
 int /*<<< orphan*/  CLK_DIVIDER_POWER_OF_TWO ; 
 TYPE_1__* ac100_clkout_prediv ; 
 int divider_get_val (unsigned long,unsigned long,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct ac100_clkout* to_ac100_clkout (struct clk_hw*) ; 

__attribute__((used)) static int ac100_clkout_set_rate(struct clk_hw *hw, unsigned long rate,
				 unsigned long prate)
{
	struct ac100_clkout *clk = to_ac100_clkout(hw);
	int div = 0, pre_div = 0;

	do {
		div = divider_get_val(rate * ac100_clkout_prediv[pre_div].div,
				      prate, NULL, AC100_CLKOUT_DIV_WIDTH,
				      CLK_DIVIDER_POWER_OF_TWO);
		if (div >= 0)
			break;
	} while (prate != AC100_RTC_32K_RATE &&
		 ac100_clkout_prediv[++pre_div].div);

	if (div < 0)
		return div;

	pre_div = ac100_clkout_prediv[pre_div].val;

	regmap_update_bits(clk->regmap, clk->offset,
			   ((1 << AC100_CLKOUT_DIV_WIDTH) - 1) << AC100_CLKOUT_DIV_SHIFT |
			   ((1 << AC100_CLKOUT_PRE_DIV_WIDTH) - 1) << AC100_CLKOUT_PRE_DIV_SHIFT,
			   (div - 1) << AC100_CLKOUT_DIV_SHIFT |
			   (pre_div - 1) << AC100_CLKOUT_PRE_DIV_SHIFT);

	return 0;
}