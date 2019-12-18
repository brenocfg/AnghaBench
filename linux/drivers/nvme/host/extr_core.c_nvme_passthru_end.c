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
typedef  int u32 ;
struct nvme_ctrl {int /*<<< orphan*/  scan_lock; TYPE_1__* subsys; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int NVME_CMD_EFFECTS_CCC ; 
 int NVME_CMD_EFFECTS_CSE_MASK ; 
 int NVME_CMD_EFFECTS_LBCC ; 
 int NVME_CMD_EFFECTS_NCC ; 
 int NVME_CMD_EFFECTS_NIC ; 
 int /*<<< orphan*/  NVME_NSID_ALL ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_init_identify (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_mpath_unfreeze (TYPE_1__*) ; 
 int /*<<< orphan*/  nvme_queue_scan (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_remove_invalid_namespaces (struct nvme_ctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_unfreeze (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_update_formats (struct nvme_ctrl*) ; 

__attribute__((used)) static void nvme_passthru_end(struct nvme_ctrl *ctrl, u32 effects)
{
	/*
	 * Revalidate LBA changes prior to unfreezing. This is necessary to
	 * prevent memory corruption if a logical block size was changed by
	 * this command.
	 */
	if (effects & NVME_CMD_EFFECTS_LBCC)
		nvme_update_formats(ctrl);
	if (effects & (NVME_CMD_EFFECTS_LBCC | NVME_CMD_EFFECTS_CSE_MASK)) {
		nvme_unfreeze(ctrl);
		nvme_mpath_unfreeze(ctrl->subsys);
		mutex_unlock(&ctrl->subsys->lock);
		nvme_remove_invalid_namespaces(ctrl, NVME_NSID_ALL);
		mutex_unlock(&ctrl->scan_lock);
	}
	if (effects & NVME_CMD_EFFECTS_CCC)
		nvme_init_identify(ctrl);
	if (effects & (NVME_CMD_EFFECTS_NIC | NVME_CMD_EFFECTS_NCC))
		nvme_queue_scan(ctrl);
}