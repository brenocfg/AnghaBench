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
struct ti_abb_reg {int fbb_sel_mask; int rbb_sel_mask; int opp_sel_mask; int opp_change_mask; } ;
struct ti_abb_info {int opp_sel; } ;
struct ti_abb {scalar_t__ ldo_base; int /*<<< orphan*/  control_reg; int /*<<< orphan*/  setup_reg; struct ti_abb_reg* regs; } ;
struct device {int dummy; } ;
struct regulator_dev {struct device dev; } ;

/* Variables and functions */
#define  TI_ABB_FAST_OPP 129 
 int TI_ABB_NOMINAL_OPP ; 
#define  TI_ABB_SLOW_OPP 128 
 int ti_abb_clear_all_txdone (struct device*,struct ti_abb*) ; 
 int /*<<< orphan*/  ti_abb_program_ldovbb (struct device*,struct ti_abb*,struct ti_abb_info*) ; 
 int /*<<< orphan*/  ti_abb_rmw (int,int,int /*<<< orphan*/ ) ; 
 int ti_abb_wait_txdone (struct device*,struct ti_abb*) ; 

__attribute__((used)) static int ti_abb_set_opp(struct regulator_dev *rdev, struct ti_abb *abb,
			  struct ti_abb_info *info)
{
	const struct ti_abb_reg *regs = abb->regs;
	struct device *dev = &rdev->dev;
	int ret;

	ret = ti_abb_clear_all_txdone(dev, abb);
	if (ret)
		goto out;

	ti_abb_rmw(regs->fbb_sel_mask | regs->rbb_sel_mask, 0, abb->setup_reg);

	switch (info->opp_sel) {
	case TI_ABB_SLOW_OPP:
		ti_abb_rmw(regs->rbb_sel_mask, 1, abb->setup_reg);
		break;
	case TI_ABB_FAST_OPP:
		ti_abb_rmw(regs->fbb_sel_mask, 1, abb->setup_reg);
		break;
	}

	/* program next state of ABB ldo */
	ti_abb_rmw(regs->opp_sel_mask, info->opp_sel, abb->control_reg);

	/*
	 * program LDO VBB vset override if needed for !bypass mode
	 * XXX: Do not switch sequence - for !bypass, LDO override reset *must*
	 * be performed *before* switch to bias mode else VBB glitches.
	 */
	if (abb->ldo_base && info->opp_sel != TI_ABB_NOMINAL_OPP)
		ti_abb_program_ldovbb(dev, abb, info);

	/* Initiate ABB ldo change */
	ti_abb_rmw(regs->opp_change_mask, 1, abb->control_reg);

	/* Wait for ABB LDO to complete transition to new Bias setting */
	ret = ti_abb_wait_txdone(dev, abb);
	if (ret)
		goto out;

	ret = ti_abb_clear_all_txdone(dev, abb);
	if (ret)
		goto out;

	/*
	 * Reset LDO VBB vset override bypass mode
	 * XXX: Do not switch sequence - for bypass, LDO override reset *must*
	 * be performed *after* switch to bypass else VBB glitches.
	 */
	if (abb->ldo_base && info->opp_sel == TI_ABB_NOMINAL_OPP)
		ti_abb_program_ldovbb(dev, abb, info);

out:
	return ret;
}