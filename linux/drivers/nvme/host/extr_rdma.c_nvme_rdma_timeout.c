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
struct request {int /*<<< orphan*/  tag; } ;
struct nvme_rdma_request {struct nvme_rdma_queue* queue; } ;
struct nvme_rdma_queue {struct nvme_rdma_ctrl* ctrl; } ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  device; } ;
struct nvme_rdma_ctrl {TYPE_1__ ctrl; int /*<<< orphan*/  err_work; } ;
typedef  enum blk_eh_timer_return { ____Placeholder_blk_eh_timer_return } blk_eh_timer_return ;

/* Variables and functions */
 int BLK_EH_DONE ; 
 int BLK_EH_RESET_TIMER ; 
 scalar_t__ NVME_CTRL_LIVE ; 
 scalar_t__ NVME_CTRL_RESETTING ; 
 struct nvme_rdma_request* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_rdma_error_recovery (struct nvme_rdma_ctrl*) ; 
 int /*<<< orphan*/  nvme_rdma_queue_idx (struct nvme_rdma_queue*) ; 
 int /*<<< orphan*/  nvme_rdma_teardown_admin_queue (struct nvme_rdma_ctrl*,int) ; 
 int /*<<< orphan*/  nvme_rdma_teardown_io_queues (struct nvme_rdma_ctrl*,int) ; 

__attribute__((used)) static enum blk_eh_timer_return
nvme_rdma_timeout(struct request *rq, bool reserved)
{
	struct nvme_rdma_request *req = blk_mq_rq_to_pdu(rq);
	struct nvme_rdma_queue *queue = req->queue;
	struct nvme_rdma_ctrl *ctrl = queue->ctrl;

	dev_warn(ctrl->ctrl.device, "I/O %d QID %d timeout\n",
		 rq->tag, nvme_rdma_queue_idx(queue));

	/*
	 * Restart the timer if a controller reset is already scheduled. Any
	 * timed out commands would be handled before entering the connecting
	 * state.
	 */
	if (ctrl->ctrl.state == NVME_CTRL_RESETTING)
		return BLK_EH_RESET_TIMER;

	if (ctrl->ctrl.state != NVME_CTRL_LIVE) {
		/*
		 * Teardown immediately if controller times out while starting
		 * or we are already started error recovery. all outstanding
		 * requests are completed on shutdown, so we return BLK_EH_DONE.
		 */
		flush_work(&ctrl->err_work);
		nvme_rdma_teardown_io_queues(ctrl, false);
		nvme_rdma_teardown_admin_queue(ctrl, false);
		return BLK_EH_DONE;
	}

	dev_warn(ctrl->ctrl.device, "starting error recovery\n");
	nvme_rdma_error_recovery(ctrl);

	return BLK_EH_RESET_TIMER;
}