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
struct nvme_ctrl {int queue_count; scalar_t__ kato; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_enable_aen (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_queue_scan (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_start_keep_alive (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_start_queues (struct nvme_ctrl*) ; 

void nvme_start_ctrl(struct nvme_ctrl *ctrl)
{
	if (ctrl->kato)
		nvme_start_keep_alive(ctrl);

	nvme_enable_aen(ctrl);

	if (ctrl->queue_count > 1) {
		nvme_queue_scan(ctrl);
		nvme_start_queues(ctrl);
	}
}