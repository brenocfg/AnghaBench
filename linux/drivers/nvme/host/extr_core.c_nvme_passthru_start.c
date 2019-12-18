#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
struct nvme_ns {int dummy; } ;
struct nvme_ctrl {TYPE_2__* subsys; int /*<<< orphan*/  scan_lock; TYPE_1__* effects; int /*<<< orphan*/  device; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/ * acs; int /*<<< orphan*/ * iocs; } ;

/* Variables and functions */
 int NVME_CMD_EFFECTS_CSE_MASK ; 
 int NVME_CMD_EFFECTS_CSUPP ; 
 int NVME_CMD_EFFECTS_LBCC ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,size_t,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int nvme_known_admin_effects (size_t) ; 
 int /*<<< orphan*/  nvme_mpath_start_freeze (TYPE_2__*) ; 
 int /*<<< orphan*/  nvme_mpath_wait_freeze (TYPE_2__*) ; 
 int /*<<< orphan*/  nvme_start_freeze (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_wait_freeze (struct nvme_ctrl*) ; 

__attribute__((used)) static u32 nvme_passthru_start(struct nvme_ctrl *ctrl, struct nvme_ns *ns,
								u8 opcode)
{
	u32 effects = 0;

	if (ns) {
		if (ctrl->effects)
			effects = le32_to_cpu(ctrl->effects->iocs[opcode]);
		if (effects & ~(NVME_CMD_EFFECTS_CSUPP | NVME_CMD_EFFECTS_LBCC))
			dev_warn(ctrl->device,
				 "IO command:%02x has unhandled effects:%08x\n",
				 opcode, effects);
		return 0;
	}

	if (ctrl->effects)
		effects = le32_to_cpu(ctrl->effects->acs[opcode]);
	effects |= nvme_known_admin_effects(opcode);

	/*
	 * For simplicity, IO to all namespaces is quiesced even if the command
	 * effects say only one namespace is affected.
	 */
	if (effects & (NVME_CMD_EFFECTS_LBCC | NVME_CMD_EFFECTS_CSE_MASK)) {
		mutex_lock(&ctrl->scan_lock);
		mutex_lock(&ctrl->subsys->lock);
		nvme_mpath_start_freeze(ctrl->subsys);
		nvme_mpath_wait_freeze(ctrl->subsys);
		nvme_start_freeze(ctrl);
		nvme_wait_freeze(ctrl);
	}
	return effects;
}