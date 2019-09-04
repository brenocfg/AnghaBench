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
struct pistachio_clk_pll {unsigned int nr_rates; TYPE_1__* rates; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {unsigned long fref; unsigned long fout; } ;

/* Variables and functions */
 struct pistachio_clk_pll* to_pistachio_pll (struct clk_hw*) ; 

__attribute__((used)) static long pll_round_rate(struct clk_hw *hw, unsigned long rate,
			   unsigned long *parent_rate)
{
	struct pistachio_clk_pll *pll = to_pistachio_pll(hw);
	unsigned int i;

	for (i = 0; i < pll->nr_rates; i++) {
		if (i > 0 && pll->rates[i].fref == *parent_rate &&
		    pll->rates[i].fout <= rate)
			return pll->rates[i - 1].fout;
	}

	return pll->rates[0].fout;
}