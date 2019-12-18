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
struct nvme_fc_ctrl {int /*<<< orphan*/  connect_work; int /*<<< orphan*/  err_work; } ;
struct nvme_ctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_fc_delete_association (struct nvme_fc_ctrl*) ; 
 struct nvme_fc_ctrl* to_fc_ctrl (struct nvme_ctrl*) ; 

__attribute__((used)) static void
nvme_fc_delete_ctrl(struct nvme_ctrl *nctrl)
{
	struct nvme_fc_ctrl *ctrl = to_fc_ctrl(nctrl);

	cancel_work_sync(&ctrl->err_work);
	cancel_delayed_work_sync(&ctrl->connect_work);
	/*
	 * kill the association on the link side.  this will block
	 * waiting for io to terminate
	 */
	nvme_fc_delete_association(ctrl);
}