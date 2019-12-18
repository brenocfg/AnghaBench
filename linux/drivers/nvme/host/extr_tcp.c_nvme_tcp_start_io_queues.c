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
struct nvme_ctrl {int queue_count; } ;

/* Variables and functions */
 int nvme_tcp_start_queue (struct nvme_ctrl*,int) ; 
 int /*<<< orphan*/  nvme_tcp_stop_queue (struct nvme_ctrl*,int) ; 

__attribute__((used)) static int nvme_tcp_start_io_queues(struct nvme_ctrl *ctrl)
{
	int i, ret = 0;

	for (i = 1; i < ctrl->queue_count; i++) {
		ret = nvme_tcp_start_queue(ctrl, i);
		if (ret)
			goto out_stop_queues;
	}

	return 0;

out_stop_queues:
	for (i--; i >= 1; i--)
		nvme_tcp_stop_queue(ctrl, i);
	return ret;
}