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
struct nvme_tcp_ctrl {TYPE_1__* queues; } ;
struct nvme_ctrl {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_TCP_Q_ALLOCATED ; 
 int /*<<< orphan*/  NVME_TCP_Q_LIVE ; 
 int /*<<< orphan*/  __nvme_tcp_stop_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int nvmf_connect_admin_queue (struct nvme_ctrl*) ; 
 int nvmf_connect_io_queue (struct nvme_ctrl*,int,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nvme_tcp_ctrl* to_tcp_ctrl (struct nvme_ctrl*) ; 

__attribute__((used)) static int nvme_tcp_start_queue(struct nvme_ctrl *nctrl, int idx)
{
	struct nvme_tcp_ctrl *ctrl = to_tcp_ctrl(nctrl);
	int ret;

	if (idx)
		ret = nvmf_connect_io_queue(nctrl, idx, false);
	else
		ret = nvmf_connect_admin_queue(nctrl);

	if (!ret) {
		set_bit(NVME_TCP_Q_LIVE, &ctrl->queues[idx].flags);
	} else {
		if (test_bit(NVME_TCP_Q_ALLOCATED, &ctrl->queues[idx].flags))
			__nvme_tcp_stop_queue(&ctrl->queues[idx]);
		dev_err(nctrl->device,
			"failed to connect queue: %d ret=%d\n", idx, ret);
	}
	return ret;
}