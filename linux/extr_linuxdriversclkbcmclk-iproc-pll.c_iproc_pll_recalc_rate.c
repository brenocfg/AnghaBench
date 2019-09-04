#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_8__ {int shift; int /*<<< orphan*/  width; scalar_t__ offset; } ;
struct TYPE_7__ {int shift; int /*<<< orphan*/  width; scalar_t__ offset; } ;
struct TYPE_6__ {int shift; int /*<<< orphan*/  width; scalar_t__ offset; } ;
struct TYPE_5__ {int shift; scalar_t__ offset; } ;
struct iproc_pll_ctrl {int flags; TYPE_4__ pdiv; TYPE_3__ ndiv_frac; TYPE_2__ ndiv_int; TYPE_1__ status; } ;
struct iproc_pll {scalar_t__ control_base; scalar_t__ status_base; struct iproc_pll_ctrl* ctrl; } ;
struct iproc_clk {struct iproc_pll* pll; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int IPROC_CLK_PLL_HAS_NDIV_FRAC ; 
 int bit_mask (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 struct iproc_clk* to_iproc_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long iproc_pll_recalc_rate(struct clk_hw *hw,
					   unsigned long parent_rate)
{
	struct iproc_clk *clk = to_iproc_clk(hw);
	struct iproc_pll *pll = clk->pll;
	const struct iproc_pll_ctrl *ctrl = pll->ctrl;
	u32 val;
	u64 ndiv, ndiv_int, ndiv_frac;
	unsigned int pdiv;
	unsigned long rate;

	if (parent_rate == 0)
		return 0;

	/* PLL needs to be locked */
	val = readl(pll->status_base + ctrl->status.offset);
	if ((val & (1 << ctrl->status.shift)) == 0)
		return 0;

	/*
	 * PLL output frequency =
	 *
	 * ((ndiv_int + ndiv_frac / 2^20) * (parent clock rate / pdiv)
	 */
	val = readl(pll->control_base + ctrl->ndiv_int.offset);
	ndiv_int = (val >> ctrl->ndiv_int.shift) &
		bit_mask(ctrl->ndiv_int.width);
	ndiv = ndiv_int << 20;

	if (ctrl->flags & IPROC_CLK_PLL_HAS_NDIV_FRAC) {
		val = readl(pll->control_base + ctrl->ndiv_frac.offset);
		ndiv_frac = (val >> ctrl->ndiv_frac.shift) &
			bit_mask(ctrl->ndiv_frac.width);
		ndiv += ndiv_frac;
	}

	val = readl(pll->control_base + ctrl->pdiv.offset);
	pdiv = (val >> ctrl->pdiv.shift) & bit_mask(ctrl->pdiv.width);

	rate = (ndiv * parent_rate) >> 20;

	if (pdiv == 0)
		rate *= 2;
	else
		rate /= pdiv;

	return rate;
}