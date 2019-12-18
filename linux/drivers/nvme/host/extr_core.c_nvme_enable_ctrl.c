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
struct nvme_ctrl {int page_size; unsigned int ctrl_config; int /*<<< orphan*/  cap; TYPE_1__* ops; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int (* reg_read64 ) (struct nvme_ctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int (* reg_write32 ) (struct nvme_ctrl*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int NVME_CAP_MPSMIN (int /*<<< orphan*/ ) ; 
 int NVME_CC_AMS_RR ; 
 unsigned int NVME_CC_CSS_NVM ; 
 int NVME_CC_ENABLE ; 
 int NVME_CC_IOCQES ; 
 int NVME_CC_IOSQES ; 
 unsigned int NVME_CC_MPS_SHIFT ; 
 int NVME_CC_SHN_NONE ; 
 int /*<<< orphan*/  NVME_REG_CAP ; 
 int /*<<< orphan*/  NVME_REG_CC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int nvme_wait_ready (struct nvme_ctrl*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct nvme_ctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub2 (struct nvme_ctrl*,int /*<<< orphan*/ ,int) ; 

int nvme_enable_ctrl(struct nvme_ctrl *ctrl)
{
	/*
	 * Default to a 4K page size, with the intention to update this
	 * path in the future to accomodate architectures with differing
	 * kernel and IO page sizes.
	 */
	unsigned dev_page_min, page_shift = 12;
	int ret;

	ret = ctrl->ops->reg_read64(ctrl, NVME_REG_CAP, &ctrl->cap);
	if (ret) {
		dev_err(ctrl->device, "Reading CAP failed (%d)\n", ret);
		return ret;
	}
	dev_page_min = NVME_CAP_MPSMIN(ctrl->cap) + 12;

	if (page_shift < dev_page_min) {
		dev_err(ctrl->device,
			"Minimum device page size %u too large for host (%u)\n",
			1 << dev_page_min, 1 << page_shift);
		return -ENODEV;
	}

	ctrl->page_size = 1 << page_shift;

	ctrl->ctrl_config = NVME_CC_CSS_NVM;
	ctrl->ctrl_config |= (page_shift - 12) << NVME_CC_MPS_SHIFT;
	ctrl->ctrl_config |= NVME_CC_AMS_RR | NVME_CC_SHN_NONE;
	ctrl->ctrl_config |= NVME_CC_IOSQES | NVME_CC_IOCQES;
	ctrl->ctrl_config |= NVME_CC_ENABLE;

	ret = ctrl->ops->reg_write32(ctrl, NVME_REG_CC, ctrl->ctrl_config);
	if (ret)
		return ret;
	return nvme_wait_ready(ctrl, ctrl->cap, true);
}