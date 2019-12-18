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
struct nvme_ctrl {int /*<<< orphan*/  tagset; int /*<<< orphan*/  connect_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_tcp_free_io_queues (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_tcp_stop_io_queues (struct nvme_ctrl*) ; 

__attribute__((used)) static void nvme_tcp_destroy_io_queues(struct nvme_ctrl *ctrl, bool remove)
{
	nvme_tcp_stop_io_queues(ctrl);
	if (remove) {
		blk_cleanup_queue(ctrl->connect_q);
		blk_mq_free_tag_set(ctrl->tagset);
	}
	nvme_tcp_free_io_queues(ctrl);
}