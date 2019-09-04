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
struct axs10x_pll_clk {struct axs10x_pll_cfg* pll_cfg; } ;
struct axs10x_pll_cfg {long rate; } ;

/* Variables and functions */
 long EINVAL ; 
 scalar_t__ abs (unsigned long) ; 
 struct axs10x_pll_clk* to_axs10x_pll_clk (struct clk_hw*) ; 

__attribute__((used)) static long axs10x_pll_round_rate(struct clk_hw *hw, unsigned long rate,
				  unsigned long *prate)
{
	int i;
	long best_rate;
	struct axs10x_pll_clk *clk = to_axs10x_pll_clk(hw);
	const struct axs10x_pll_cfg *pll_cfg = clk->pll_cfg;

	if (pll_cfg[0].rate == 0)
		return -EINVAL;

	best_rate = pll_cfg[0].rate;

	for (i = 1; pll_cfg[i].rate != 0; i++) {
		if (abs(rate - pll_cfg[i].rate) < abs(rate - best_rate))
			best_rate = pll_cfg[i].rate;
	}

	return best_rate;
}