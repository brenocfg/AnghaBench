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
struct nvme_ctrl {int quirks; int /*<<< orphan*/  cap; int /*<<< orphan*/  ctrl_config; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* reg_write32 ) (struct nvme_ctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_CC_ENABLE ; 
 int /*<<< orphan*/  NVME_CC_SHN_MASK ; 
 int /*<<< orphan*/  NVME_QUIRK_DELAY_AMOUNT ; 
 int NVME_QUIRK_DELAY_BEFORE_CHK_RDY ; 
 int /*<<< orphan*/  NVME_REG_CC ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int nvme_wait_ready (struct nvme_ctrl*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct nvme_ctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nvme_disable_ctrl(struct nvme_ctrl *ctrl)
{
	int ret;

	ctrl->ctrl_config &= ~NVME_CC_SHN_MASK;
	ctrl->ctrl_config &= ~NVME_CC_ENABLE;

	ret = ctrl->ops->reg_write32(ctrl, NVME_REG_CC, ctrl->ctrl_config);
	if (ret)
		return ret;

	if (ctrl->quirks & NVME_QUIRK_DELAY_BEFORE_CHK_RDY)
		msleep(NVME_QUIRK_DELAY_AMOUNT);

	return nvme_wait_ready(ctrl, ctrl->cap, false);
}