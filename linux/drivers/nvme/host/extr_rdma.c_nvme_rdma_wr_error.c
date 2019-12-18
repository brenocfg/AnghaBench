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
struct nvme_rdma_queue {struct nvme_rdma_ctrl* ctrl; } ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  device; } ;
struct nvme_rdma_ctrl {TYPE_1__ ctrl; } ;
struct ib_wc {int /*<<< orphan*/  status; int /*<<< orphan*/  wr_cqe; } ;
struct ib_cq {struct nvme_rdma_queue* cq_context; } ;

/* Variables and functions */
 scalar_t__ NVME_CTRL_LIVE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_wc_status_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_rdma_error_recovery (struct nvme_rdma_ctrl*) ; 

__attribute__((used)) static void nvme_rdma_wr_error(struct ib_cq *cq, struct ib_wc *wc,
		const char *op)
{
	struct nvme_rdma_queue *queue = cq->cq_context;
	struct nvme_rdma_ctrl *ctrl = queue->ctrl;

	if (ctrl->ctrl.state == NVME_CTRL_LIVE)
		dev_info(ctrl->ctrl.device,
			     "%s for CQE 0x%p failed with status %s (%d)\n",
			     op, wc->wr_cqe,
			     ib_wc_status_msg(wc->status), wc->status);
	nvme_rdma_error_recovery(ctrl);
}