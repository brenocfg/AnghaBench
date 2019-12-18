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
struct TYPE_2__ {int /*<<< orphan*/  tagset; int /*<<< orphan*/  connect_q; } ;
struct nvme_rdma_ctrl {TYPE_1__ ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_rdma_free_io_queues (struct nvme_rdma_ctrl*) ; 

__attribute__((used)) static void nvme_rdma_destroy_io_queues(struct nvme_rdma_ctrl *ctrl,
		bool remove)
{
	if (remove) {
		blk_cleanup_queue(ctrl->ctrl.connect_q);
		blk_mq_free_tag_set(ctrl->ctrl.tagset);
	}
	nvme_rdma_free_io_queues(ctrl);
}