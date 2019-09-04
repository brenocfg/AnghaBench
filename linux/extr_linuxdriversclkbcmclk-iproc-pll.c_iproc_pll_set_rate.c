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
struct iproc_pll_vco_param {int dummy; } ;
struct iproc_pll_ctrl {int flags; } ;
struct iproc_pll {struct iproc_pll_vco_param* vco_param; struct iproc_pll_ctrl* ctrl; } ;
struct iproc_clk {struct iproc_pll* pll; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int IPROC_CLK_PLL_CALC_PARAM ; 
 int pll_calc_param (unsigned long,unsigned long,struct iproc_pll_vco_param*) ; 
 int pll_get_rate_index (struct iproc_pll*,unsigned long) ; 
 int pll_set_rate (struct iproc_clk*,struct iproc_pll_vco_param*,unsigned long) ; 
 struct iproc_clk* to_iproc_clk (struct clk_hw*) ; 

__attribute__((used)) static int iproc_pll_set_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long parent_rate)
{
	struct iproc_clk *clk = to_iproc_clk(hw);
	struct iproc_pll *pll = clk->pll;
	const struct iproc_pll_ctrl *ctrl = pll->ctrl;
	struct iproc_pll_vco_param vco_param;
	int rate_index, ret;

	if (ctrl->flags & IPROC_CLK_PLL_CALC_PARAM) {
		ret = pll_calc_param(rate, parent_rate, &vco_param);
		if (ret)
			return ret;
	} else {
		rate_index = pll_get_rate_index(pll, rate);
		if (rate_index < 0)
			return rate_index;

		vco_param = pll->vco_param[rate_index];
	}

	ret = pll_set_rate(clk, &vco_param, parent_rate);
	return ret;
}