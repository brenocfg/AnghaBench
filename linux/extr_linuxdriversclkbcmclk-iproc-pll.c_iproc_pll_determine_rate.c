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
struct iproc_pll_vco_param {scalar_t__ rate; } ;
struct iproc_pll_ctrl {int flags; } ;
struct iproc_pll {unsigned int num_vco_entries; TYPE_1__* vco_param; struct iproc_pll_ctrl* ctrl; } ;
struct iproc_clk {struct iproc_pll* pll; } ;
struct clk_rate_request {scalar_t__ rate; scalar_t__ best_parent_rate; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {scalar_t__ rate; } ;

/* Variables and functions */
 int EINVAL ; 
 int IPROC_CLK_PLL_CALC_PARAM ; 
 unsigned long ULONG_MAX ; 
 unsigned long abs (scalar_t__) ; 
 int pll_calc_param (scalar_t__,scalar_t__,struct iproc_pll_vco_param*) ; 
 struct iproc_clk* to_iproc_clk (struct clk_hw*) ; 

__attribute__((used)) static int iproc_pll_determine_rate(struct clk_hw *hw,
		struct clk_rate_request *req)
{
	unsigned int  i;
	struct iproc_clk *clk = to_iproc_clk(hw);
	struct iproc_pll *pll = clk->pll;
	const struct iproc_pll_ctrl *ctrl = pll->ctrl;
	unsigned long  diff, best_diff;
	unsigned int  best_idx = 0;
	int ret;

	if (req->rate == 0 || req->best_parent_rate == 0)
		return -EINVAL;

	if (ctrl->flags & IPROC_CLK_PLL_CALC_PARAM) {
		struct iproc_pll_vco_param vco_param;

		ret = pll_calc_param(req->rate, req->best_parent_rate,
					&vco_param);
		if (ret)
			return ret;

		req->rate = vco_param.rate;
		return 0;
	}

	if (!pll->vco_param)
		return -EINVAL;

	best_diff = ULONG_MAX;
	for (i = 0; i < pll->num_vco_entries; i++) {
		diff = abs(req->rate - pll->vco_param[i].rate);
		if (diff <= best_diff) {
			best_diff = diff;
			best_idx = i;
		}
		/* break now if perfect match */
		if (diff == 0)
			break;
	}

	req->rate = pll->vco_param[best_idx].rate;

	return 0;
}