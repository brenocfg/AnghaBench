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
struct clk_zx_pll {TYPE_1__* lookup_table; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {long rate; } ;

/* Variables and functions */
 int rate_to_idx (struct clk_zx_pll*,unsigned long) ; 
 struct clk_zx_pll* to_clk_zx_pll (struct clk_hw*) ; 

__attribute__((used)) static long zx_pll_round_rate(struct clk_hw *hw, unsigned long rate,
			      unsigned long *prate)
{
	struct clk_zx_pll *zx_pll = to_clk_zx_pll(hw);
	int idx;

	idx = rate_to_idx(zx_pll, rate);

	return zx_pll->lookup_table[idx].rate;
}