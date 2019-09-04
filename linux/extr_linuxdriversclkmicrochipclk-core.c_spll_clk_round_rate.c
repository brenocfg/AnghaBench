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
struct pic32_sys_pll {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct pic32_sys_pll* clkhw_to_spll (struct clk_hw*) ; 
 long spll_calc_mult_div (struct pic32_sys_pll*,unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static long spll_clk_round_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long *parent_rate)
{
	struct pic32_sys_pll *pll = clkhw_to_spll(hw);

	return spll_calc_mult_div(pll, rate, *parent_rate, NULL, NULL);
}