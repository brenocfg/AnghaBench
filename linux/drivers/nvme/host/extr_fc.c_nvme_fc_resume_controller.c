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
struct TYPE_2__ {int state; int /*<<< orphan*/  device; } ;
struct nvme_fc_ctrl {int /*<<< orphan*/  connect_work; int /*<<< orphan*/  cnum; TYPE_1__ ctrl; } ;

/* Variables and functions */
#define  NVME_CTRL_CONNECTING 130 
#define  NVME_CTRL_NEW 129 
#define  NVME_CTRL_RESETTING 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_wq ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvme_fc_resume_controller(struct nvme_fc_ctrl *ctrl)
{
	switch (ctrl->ctrl.state) {
	case NVME_CTRL_NEW:
	case NVME_CTRL_CONNECTING:
		/*
		 * As all reconnects were suppressed, schedule a
		 * connect.
		 */
		dev_info(ctrl->ctrl.device,
			"NVME-FC{%d}: connectivity re-established. "
			"Attempting reconnect\n", ctrl->cnum);

		queue_delayed_work(nvme_wq, &ctrl->connect_work, 0);
		break;

	case NVME_CTRL_RESETTING:
		/*
		 * Controller is already in the process of terminating the
		 * association. No need to do anything further. The reconnect
		 * step will naturally occur after the reset completes.
		 */
		break;

	default:
		/* no action to take - let it delete */
		break;
	}
}