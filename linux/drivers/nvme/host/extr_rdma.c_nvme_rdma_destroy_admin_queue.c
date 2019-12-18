#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {int /*<<< orphan*/  admin_tagset; int /*<<< orphan*/  fabrics_q; int /*<<< orphan*/  admin_q; } ;
struct nvme_rdma_ctrl {int /*<<< orphan*/ * queues; TYPE_3__ async_event_sqe; TYPE_1__* device; TYPE_2__ ctrl; } ;
struct nvme_command {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_rdma_free_qe (int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_rdma_free_queue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_rdma_destroy_admin_queue(struct nvme_rdma_ctrl *ctrl,
		bool remove)
{
	if (remove) {
		blk_cleanup_queue(ctrl->ctrl.admin_q);
		blk_cleanup_queue(ctrl->ctrl.fabrics_q);
		blk_mq_free_tag_set(ctrl->ctrl.admin_tagset);
	}
	if (ctrl->async_event_sqe.data) {
		nvme_rdma_free_qe(ctrl->device->dev, &ctrl->async_event_sqe,
				sizeof(struct nvme_command), DMA_TO_DEVICE);
		ctrl->async_event_sqe.data = NULL;
	}
	nvme_rdma_free_queue(&ctrl->queues[0]);
}