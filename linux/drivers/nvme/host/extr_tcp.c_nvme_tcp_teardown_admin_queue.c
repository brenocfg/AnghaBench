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
struct nvme_ctrl {int /*<<< orphan*/  admin_q; scalar_t__ admin_tagset; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_quiesce_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_tagset_busy_iter (scalar_t__,int /*<<< orphan*/ ,struct nvme_ctrl*) ; 
 int /*<<< orphan*/  blk_mq_tagset_wait_completed_request (scalar_t__) ; 
 int /*<<< orphan*/  blk_mq_unquiesce_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_cancel_request ; 
 int /*<<< orphan*/  nvme_tcp_destroy_admin_queue (struct nvme_ctrl*,int) ; 
 int /*<<< orphan*/  nvme_tcp_stop_queue (struct nvme_ctrl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvme_tcp_teardown_admin_queue(struct nvme_ctrl *ctrl,
		bool remove)
{
	blk_mq_quiesce_queue(ctrl->admin_q);
	nvme_tcp_stop_queue(ctrl, 0);
	if (ctrl->admin_tagset) {
		blk_mq_tagset_busy_iter(ctrl->admin_tagset,
			nvme_cancel_request, ctrl);
		blk_mq_tagset_wait_completed_request(ctrl->admin_tagset);
	}
	if (remove)
		blk_mq_unquiesce_queue(ctrl->admin_q);
	nvme_tcp_destroy_admin_queue(ctrl, remove);
}