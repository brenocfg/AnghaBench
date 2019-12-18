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
struct nvme_ctrl {int queue_count; scalar_t__ tagset; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_tagset_busy_iter (scalar_t__,int /*<<< orphan*/ ,struct nvme_ctrl*) ; 
 int /*<<< orphan*/  blk_mq_tagset_wait_completed_request (scalar_t__) ; 
 int /*<<< orphan*/  nvme_cancel_request ; 
 int /*<<< orphan*/  nvme_start_queues (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_stop_queues (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_tcp_destroy_io_queues (struct nvme_ctrl*,int) ; 
 int /*<<< orphan*/  nvme_tcp_stop_io_queues (struct nvme_ctrl*) ; 

__attribute__((used)) static void nvme_tcp_teardown_io_queues(struct nvme_ctrl *ctrl,
		bool remove)
{
	if (ctrl->queue_count <= 1)
		return;
	nvme_stop_queues(ctrl);
	nvme_tcp_stop_io_queues(ctrl);
	if (ctrl->tagset) {
		blk_mq_tagset_busy_iter(ctrl->tagset,
			nvme_cancel_request, ctrl);
		blk_mq_tagset_wait_completed_request(ctrl->tagset);
	}
	if (remove)
		nvme_start_queues(ctrl);
	nvme_tcp_destroy_io_queues(ctrl, remove);
}