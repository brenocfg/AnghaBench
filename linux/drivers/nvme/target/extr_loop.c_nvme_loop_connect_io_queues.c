#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int queue_count; } ;
struct nvme_loop_ctrl {TYPE_1__* queues; TYPE_2__ ctrl; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_LOOP_Q_LIVE ; 
 int nvmf_connect_io_queue (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvme_loop_connect_io_queues(struct nvme_loop_ctrl *ctrl)
{
	int i, ret;

	for (i = 1; i < ctrl->ctrl.queue_count; i++) {
		ret = nvmf_connect_io_queue(&ctrl->ctrl, i, false);
		if (ret)
			return ret;
		set_bit(NVME_LOOP_Q_LIVE, &ctrl->queues[i].flags);
	}

	return 0;
}