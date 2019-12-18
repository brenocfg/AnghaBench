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
struct TYPE_2__ {int /*<<< orphan*/ * cqe; int /*<<< orphan*/ * cmd; } ;
struct nvme_loop_iod {int /*<<< orphan*/  work; int /*<<< orphan*/ * queue; int /*<<< orphan*/  cqe; TYPE_1__ req; int /*<<< orphan*/  cmd; } ;
struct nvme_loop_ctrl {int /*<<< orphan*/ * queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_loop_execute_work ; 

__attribute__((used)) static int nvme_loop_init_iod(struct nvme_loop_ctrl *ctrl,
		struct nvme_loop_iod *iod, unsigned int queue_idx)
{
	iod->req.cmd = &iod->cmd;
	iod->req.cqe = &iod->cqe;
	iod->queue = &ctrl->queues[queue_idx];
	INIT_WORK(&iod->work, nvme_loop_execute_work);
	return 0;
}