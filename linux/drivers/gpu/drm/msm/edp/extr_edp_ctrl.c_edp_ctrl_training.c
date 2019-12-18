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
struct edp_ctrl {int /*<<< orphan*/  phy; int /*<<< orphan*/  power_on; } ;

/* Variables and functions */
 int EDP_TRAIN_RECONFIG ; 
 int EINVAL ; 
 int /*<<< orphan*/  edp_ctrl_irq_enable (struct edp_ctrl*,int) ; 
 int /*<<< orphan*/  edp_ctrl_link_enable (struct edp_ctrl*,int) ; 
 int edp_do_link_train (struct edp_ctrl*) ; 
 int /*<<< orphan*/  msm_edp_phy_ctrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int edp_ctrl_training(struct edp_ctrl *ctrl)
{
	int ret;

	/* Do link training only when power is on */
	if (!ctrl->power_on)
		return -EINVAL;

train_start:
	ret = edp_do_link_train(ctrl);
	if (ret == EDP_TRAIN_RECONFIG) {
		/* Re-configure main link */
		edp_ctrl_irq_enable(ctrl, 0);
		edp_ctrl_link_enable(ctrl, 0);
		msm_edp_phy_ctrl(ctrl->phy, 0);

		/* Make sure link is fully disabled */
		wmb();
		usleep_range(500, 1000);

		msm_edp_phy_ctrl(ctrl->phy, 1);
		edp_ctrl_link_enable(ctrl, 1);
		edp_ctrl_irq_enable(ctrl, 1);
		goto train_start;
	}

	return ret;
}