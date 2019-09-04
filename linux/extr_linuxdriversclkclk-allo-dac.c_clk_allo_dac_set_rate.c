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
struct clk_allo_hw {int mode; } ;

/* Variables and functions */
 unsigned long CLK_44EN_RATE ; 
 scalar_t__ clk_allo_dac_round_rate (struct clk_hw*,unsigned long,unsigned long*) ; 
 struct clk_allo_hw* to_allo_clk (struct clk_hw*) ; 

__attribute__((used)) static int clk_allo_dac_set_rate(struct clk_hw *hw,
	unsigned long rate, unsigned long parent_rate)
{
	unsigned long actual_rate;
	struct clk_allo_hw *clk = to_allo_clk(hw);

	actual_rate = (unsigned long)clk_allo_dac_round_rate(hw, rate,
		&parent_rate);
	clk->mode = (actual_rate == CLK_44EN_RATE) ? 0 : 1;
	return 0;
}