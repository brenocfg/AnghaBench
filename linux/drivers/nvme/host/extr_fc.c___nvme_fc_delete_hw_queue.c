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
struct nvme_fc_queue {int /*<<< orphan*/ * lldd_handle; } ;
struct nvme_fc_ctrl {TYPE_2__* lport; } ;
struct TYPE_4__ {int /*<<< orphan*/  localport; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* delete_queue ) (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__nvme_fc_delete_hw_queue(struct nvme_fc_ctrl *ctrl,
	struct nvme_fc_queue *queue, unsigned int qidx)
{
	if (ctrl->lport->ops->delete_queue)
		ctrl->lport->ops->delete_queue(&ctrl->lport->localport, qidx,
				queue->lldd_handle);
	queue->lldd_handle = NULL;
}