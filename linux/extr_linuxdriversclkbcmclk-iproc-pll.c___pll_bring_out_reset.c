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
typedef  unsigned int u32 ;
struct iproc_pll_reset_ctrl {scalar_t__ offset; int /*<<< orphan*/  p_reset_shift; int /*<<< orphan*/  reset_shift; } ;
struct iproc_pll_dig_filter_ctrl {unsigned int ki_shift; unsigned int kp_shift; unsigned int ka_shift; scalar_t__ offset; int /*<<< orphan*/  ka_width; int /*<<< orphan*/  kp_width; int /*<<< orphan*/  ki_width; } ;
struct iproc_pll_ctrl {int flags; struct iproc_pll_dig_filter_ctrl dig_filter; struct iproc_pll_reset_ctrl reset; } ;
struct iproc_pll {scalar_t__ control_base; struct iproc_pll_ctrl* ctrl; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int IPROC_CLK_PLL_RESET_ACTIVE_LOW ; 
 unsigned int bit_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iproc_pll_write (struct iproc_pll*,scalar_t__,scalar_t__,unsigned int) ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static void __pll_bring_out_reset(struct iproc_pll *pll, unsigned int kp,
				  unsigned int ka, unsigned int ki)
{
	u32 val;
	const struct iproc_pll_ctrl *ctrl = pll->ctrl;
	const struct iproc_pll_reset_ctrl *reset = &ctrl->reset;
	const struct iproc_pll_dig_filter_ctrl *dig_filter = &ctrl->dig_filter;

	val = readl(pll->control_base + dig_filter->offset);
	val &= ~(bit_mask(dig_filter->ki_width) << dig_filter->ki_shift |
		bit_mask(dig_filter->kp_width) << dig_filter->kp_shift |
		bit_mask(dig_filter->ka_width) << dig_filter->ka_shift);
	val |= ki << dig_filter->ki_shift | kp << dig_filter->kp_shift |
	       ka << dig_filter->ka_shift;
	iproc_pll_write(pll, pll->control_base, dig_filter->offset, val);

	val = readl(pll->control_base + reset->offset);
	if (ctrl->flags & IPROC_CLK_PLL_RESET_ACTIVE_LOW)
		val &= ~(BIT(reset->reset_shift) | BIT(reset->p_reset_shift));
	else
		val |= BIT(reset->reset_shift) | BIT(reset->p_reset_shift);
	iproc_pll_write(pll, pll->control_base, reset->offset, val);
}