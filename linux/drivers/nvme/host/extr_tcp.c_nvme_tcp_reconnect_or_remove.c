#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvme_ctrl {scalar_t__ state; int /*<<< orphan*/  device; TYPE_1__* opts; } ;
struct TYPE_4__ {int /*<<< orphan*/  connect_work; } ;
struct TYPE_3__ {int reconnect_delay; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ NVME_CTRL_CONNECTING ; 
 scalar_t__ NVME_CTRL_LIVE ; 
 scalar_t__ NVME_CTRL_NEW ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nvme_delete_ctrl (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_wq ; 
 scalar_t__ nvmf_should_reconnect (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* to_tcp_ctrl (struct nvme_ctrl*) ; 

__attribute__((used)) static void nvme_tcp_reconnect_or_remove(struct nvme_ctrl *ctrl)
{
	/* If we are resetting/deleting then do nothing */
	if (ctrl->state != NVME_CTRL_CONNECTING) {
		WARN_ON_ONCE(ctrl->state == NVME_CTRL_NEW ||
			ctrl->state == NVME_CTRL_LIVE);
		return;
	}

	if (nvmf_should_reconnect(ctrl)) {
		dev_info(ctrl->device, "Reconnecting in %d seconds...\n",
			ctrl->opts->reconnect_delay);
		queue_delayed_work(nvme_wq, &to_tcp_ctrl(ctrl)->connect_work,
				ctrl->opts->reconnect_delay * HZ);
	} else {
		dev_info(ctrl->device, "Removing controller...\n");
		nvme_delete_ctrl(ctrl);
	}
}