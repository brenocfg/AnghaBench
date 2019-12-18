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
struct nvme_ctrl {unsigned int queue_count; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int __nvme_tcp_alloc_io_queues (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int nvme_set_queue_count (struct nvme_ctrl*,unsigned int*) ; 
 unsigned int nvme_tcp_nr_io_queues (struct nvme_ctrl*) ; 
 int /*<<< orphan*/  nvme_tcp_set_io_queues (struct nvme_ctrl*,unsigned int) ; 

__attribute__((used)) static int nvme_tcp_alloc_io_queues(struct nvme_ctrl *ctrl)
{
	unsigned int nr_io_queues;
	int ret;

	nr_io_queues = nvme_tcp_nr_io_queues(ctrl);
	ret = nvme_set_queue_count(ctrl, &nr_io_queues);
	if (ret)
		return ret;

	ctrl->queue_count = nr_io_queues + 1;
	if (ctrl->queue_count < 2)
		return 0;

	dev_info(ctrl->device,
		"creating %d I/O queues.\n", nr_io_queues);

	nvme_tcp_set_io_queues(ctrl, nr_io_queues);

	return __nvme_tcp_alloc_io_queues(ctrl);
}