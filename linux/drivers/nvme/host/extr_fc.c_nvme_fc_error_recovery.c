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
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  device; } ;
struct nvme_fc_ctrl {TYPE_1__ ctrl; int /*<<< orphan*/  cnum; int /*<<< orphan*/  err_work_active; int /*<<< orphan*/  err_work; } ;

/* Variables and functions */
 scalar_t__ NVME_CTRL_CONNECTING ; 
 scalar_t__ NVME_CTRL_LIVE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int atomic_xchg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  nvme_fc_wq ; 
 int /*<<< orphan*/  nvme_reset_ctrl (TYPE_1__*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvme_fc_error_recovery(struct nvme_fc_ctrl *ctrl, char *errmsg)
{
	int active;

	/*
	 * if an error (io timeout, etc) while (re)connecting,
	 * it's an error on creating the new association.
	 * Start the error recovery thread if it hasn't already
	 * been started. It is expected there could be multiple
	 * ios hitting this path before things are cleaned up.
	 */
	if (ctrl->ctrl.state == NVME_CTRL_CONNECTING) {
		active = atomic_xchg(&ctrl->err_work_active, 1);
		if (!active && !queue_work(nvme_fc_wq, &ctrl->err_work)) {
			atomic_set(&ctrl->err_work_active, 0);
			WARN_ON(1);
		}
		return;
	}

	/* Otherwise, only proceed if in LIVE state - e.g. on first error */
	if (ctrl->ctrl.state != NVME_CTRL_LIVE)
		return;

	dev_warn(ctrl->ctrl.device,
		"NVME-FC{%d}: transport association error detected: %s\n",
		ctrl->cnum, errmsg);
	dev_warn(ctrl->ctrl.device,
		"NVME-FC{%d}: resetting controller\n", ctrl->cnum);

	nvme_reset_ctrl(&ctrl->ctrl);
}