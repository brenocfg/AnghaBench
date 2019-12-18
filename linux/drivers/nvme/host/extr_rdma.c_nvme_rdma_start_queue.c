#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvme_rdma_queue {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct nvme_rdma_ctrl {TYPE_1__ ctrl; struct nvme_rdma_queue* queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_RDMA_Q_ALLOCATED ; 
 int /*<<< orphan*/  NVME_RDMA_Q_LIVE ; 
 int /*<<< orphan*/  __nvme_rdma_stop_queue (struct nvme_rdma_queue*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int) ; 
 int nvme_rdma_poll_queue (struct nvme_rdma_queue*) ; 
 int nvmf_connect_admin_queue (TYPE_1__*) ; 
 int nvmf_connect_io_queue (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvme_rdma_start_queue(struct nvme_rdma_ctrl *ctrl, int idx)
{
	struct nvme_rdma_queue *queue = &ctrl->queues[idx];
	bool poll = nvme_rdma_poll_queue(queue);
	int ret;

	if (idx)
		ret = nvmf_connect_io_queue(&ctrl->ctrl, idx, poll);
	else
		ret = nvmf_connect_admin_queue(&ctrl->ctrl);

	if (!ret) {
		set_bit(NVME_RDMA_Q_LIVE, &queue->flags);
	} else {
		if (test_bit(NVME_RDMA_Q_ALLOCATED, &queue->flags))
			__nvme_rdma_stop_queue(queue);
		dev_info(ctrl->ctrl.device,
			"failed to connect queue: %d ret=%d\n", idx, ret);
	}
	return ret;
}