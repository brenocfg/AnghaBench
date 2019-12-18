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
struct TYPE_2__ {int /*<<< orphan*/  val; scalar_t__ div; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC100_CLKOUT_DIV_WIDTH ; 
 unsigned long AC100_RTC_32K_RATE ; 
 int /*<<< orphan*/  CLK_DIVIDER_POWER_OF_TWO ; 
 unsigned long DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_1__* ac100_clkout_prediv ; 
 long divider_round_rate (struct clk_hw*,unsigned long,unsigned long*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long ac100_clkout_round_rate(struct clk_hw *hw, unsigned long rate,
				    unsigned long prate)
{
	unsigned long best_rate = 0, tmp_rate, tmp_prate;
	int i;

	if (prate == AC100_RTC_32K_RATE)
		return divider_round_rate(hw, rate, &prate, NULL,
					  AC100_CLKOUT_DIV_WIDTH,
					  CLK_DIVIDER_POWER_OF_TWO);

	for (i = 0; ac100_clkout_prediv[i].div; i++) {
		tmp_prate = DIV_ROUND_UP(prate, ac100_clkout_prediv[i].val);
		tmp_rate = divider_round_rate(hw, rate, &tmp_prate, NULL,
					      AC100_CLKOUT_DIV_WIDTH,
					      CLK_DIVIDER_POWER_OF_TWO);

		if (tmp_rate > rate)
			continue;
		if (rate - tmp_rate < best_rate - tmp_rate)
			best_rate = tmp_rate;
	}

	return best_rate;
}