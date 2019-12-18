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
struct nvme_fc_remote_port {scalar_t__ port_state; int /*<<< orphan*/  dev_loss_tmo; } ;
struct nvme_fc_rport {unsigned long dev_loss_end; struct nvme_fc_remote_port remoteport; } ;
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/  device; int /*<<< orphan*/  nr_reconnects; TYPE_1__* opts; } ;
struct nvme_fc_ctrl {TYPE_2__ ctrl; int /*<<< orphan*/  cnum; int /*<<< orphan*/  connect_work; struct nvme_fc_rport* rport; } ;
struct TYPE_4__ {unsigned long reconnect_delay; } ;

/* Variables and functions */
 scalar_t__ FC_OBJSTATE_ONLINE ; 
 unsigned long HZ ; 
 scalar_t__ NVME_CTRL_CONNECTING ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  nvme_delete_ctrl (TYPE_2__*) ; 
 int /*<<< orphan*/  nvme_wq ; 
 scalar_t__ nvmf_should_reconnect (TYPE_2__*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static void
nvme_fc_reconnect_or_delete(struct nvme_fc_ctrl *ctrl, int status)
{
	struct nvme_fc_rport *rport = ctrl->rport;
	struct nvme_fc_remote_port *portptr = &rport->remoteport;
	unsigned long recon_delay = ctrl->ctrl.opts->reconnect_delay * HZ;
	bool recon = true;

	if (ctrl->ctrl.state != NVME_CTRL_CONNECTING)
		return;

	if (portptr->port_state == FC_OBJSTATE_ONLINE)
		dev_info(ctrl->ctrl.device,
			"NVME-FC{%d}: reset: Reconnect attempt failed (%d)\n",
			ctrl->cnum, status);
	else if (time_after_eq(jiffies, rport->dev_loss_end))
		recon = false;

	if (recon && nvmf_should_reconnect(&ctrl->ctrl)) {
		if (portptr->port_state == FC_OBJSTATE_ONLINE)
			dev_info(ctrl->ctrl.device,
				"NVME-FC{%d}: Reconnect attempt in %ld "
				"seconds\n",
				ctrl->cnum, recon_delay / HZ);
		else if (time_after(jiffies + recon_delay, rport->dev_loss_end))
			recon_delay = rport->dev_loss_end - jiffies;

		queue_delayed_work(nvme_wq, &ctrl->connect_work, recon_delay);
	} else {
		if (portptr->port_state == FC_OBJSTATE_ONLINE)
			dev_warn(ctrl->ctrl.device,
				"NVME-FC{%d}: Max reconnect attempts (%d) "
				"reached.\n",
				ctrl->cnum, ctrl->ctrl.nr_reconnects);
		else
			dev_warn(ctrl->ctrl.device,
				"NVME-FC{%d}: dev_loss_tmo (%d) expired "
				"while waiting for remoteport connectivity.\n",
				ctrl->cnum, portptr->dev_loss_tmo);
		WARN_ON(nvme_delete_ctrl(&ctrl->ctrl));
	}
}