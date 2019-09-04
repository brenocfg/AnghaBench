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
typedef  unsigned int u32 ;
struct iproc_pll {scalar_t__ control_base; } ;
struct TYPE_2__ {unsigned int shift; scalar_t__ offset; int /*<<< orphan*/  width; } ;
struct iproc_clk_ctrl {int flags; TYPE_1__ mdiv; } ;
struct iproc_clk {struct iproc_pll* pll; struct iproc_clk_ctrl* ctrl; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (unsigned long,unsigned long) ; 
 int EINVAL ; 
 int IPROC_CLK_MCLK_DIV_BY_2 ; 
 unsigned int bit_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iproc_pll_write (struct iproc_pll*,scalar_t__,scalar_t__,unsigned int) ; 
 unsigned int readl (scalar_t__) ; 
 struct iproc_clk* to_iproc_clk (struct clk_hw*) ; 

__attribute__((used)) static int iproc_clk_set_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long parent_rate)
{
	struct iproc_clk *clk = to_iproc_clk(hw);
	const struct iproc_clk_ctrl *ctrl = clk->ctrl;
	struct iproc_pll *pll = clk->pll;
	u32 val;
	unsigned int div;

	if (rate == 0 || parent_rate == 0)
		return -EINVAL;

	div = DIV_ROUND_CLOSEST(parent_rate, rate);
	if (ctrl->flags & IPROC_CLK_MCLK_DIV_BY_2)
		div /=  2;

	if (div > 256)
		return -EINVAL;

	val = readl(pll->control_base + ctrl->mdiv.offset);
	if (div == 256) {
		val &= ~(bit_mask(ctrl->mdiv.width) << ctrl->mdiv.shift);
	} else {
		val &= ~(bit_mask(ctrl->mdiv.width) << ctrl->mdiv.shift);
		val |= div << ctrl->mdiv.shift;
	}
	iproc_pll_write(pll, pll->control_base, ctrl->mdiv.offset, val);

	return 0;
}