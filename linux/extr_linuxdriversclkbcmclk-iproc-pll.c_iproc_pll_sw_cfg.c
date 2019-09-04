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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ offset; int /*<<< orphan*/  shift; } ;
struct iproc_pll_ctrl {int flags; TYPE_1__ sw_ctrl; } ;
struct iproc_pll {scalar_t__ control_base; struct iproc_pll_ctrl* ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int IPROC_CLK_PLL_NEEDS_SW_CFG ; 
 int /*<<< orphan*/  iproc_pll_write (struct iproc_pll*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static void iproc_pll_sw_cfg(struct iproc_pll *pll)
{
	const struct iproc_pll_ctrl *ctrl = pll->ctrl;

	if (ctrl->flags & IPROC_CLK_PLL_NEEDS_SW_CFG) {
		u32 val;

		val = readl(pll->control_base + ctrl->sw_ctrl.offset);
		val |= BIT(ctrl->sw_ctrl.shift);
		iproc_pll_write(pll, pll->control_base, ctrl->sw_ctrl.offset,
				val);
	}
}