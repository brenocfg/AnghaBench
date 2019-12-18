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
struct nvme_fc_queue {int qnum; int cmnd_capsule_len; int /*<<< orphan*/  dev; int /*<<< orphan*/  csn; struct nvme_fc_ctrl* ctrl; } ;
struct TYPE_2__ {int ioccsz; } ;
struct nvme_fc_ctrl {TYPE_1__ ctrl; int /*<<< orphan*/  dev; struct nvme_fc_queue* queues; } ;
struct nvme_command {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nvme_fc_queue*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nvme_fc_init_queue(struct nvme_fc_ctrl *ctrl, int idx)
{
	struct nvme_fc_queue *queue;

	queue = &ctrl->queues[idx];
	memset(queue, 0, sizeof(*queue));
	queue->ctrl = ctrl;
	queue->qnum = idx;
	atomic_set(&queue->csn, 0);
	queue->dev = ctrl->dev;

	if (idx > 0)
		queue->cmnd_capsule_len = ctrl->ctrl.ioccsz * 16;
	else
		queue->cmnd_capsule_len = sizeof(struct nvme_command);

	/*
	 * Considered whether we should allocate buffers for all SQEs
	 * and CQEs and dma map them - mapping their respective entries
	 * into the request structures (kernel vm addr and dma address)
	 * thus the driver could use the buffers/mappings directly.
	 * It only makes sense if the LLDD would use them for its
	 * messaging api. It's very unlikely most adapter api's would use
	 * a native NVME sqe/cqe. More reasonable if FC-NVME IU payload
	 * structures were used instead.
	 */
}