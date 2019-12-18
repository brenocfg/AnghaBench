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
 int /*<<< orphan*/  nvme_tcp_free_queue (struct nvme_ctrl*,int) ; 

__attribute__((used)) static void nvme_tcp_free_io_queues(struct nvme_ctrl *ctrl)
{
	int i;

	for (i = 1; i < ctrl->queue_count; i++)
		nvme_tcp_free_queue(ctrl, i);
}