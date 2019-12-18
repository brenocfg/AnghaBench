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
struct nvme_fc_queue {struct blk_mq_hw_ctx* hctx; } ;
struct nvme_fc_ctrl {struct nvme_fc_queue* queues; } ;
struct blk_mq_hw_ctx {struct nvme_fc_queue* driver_data; } ;

/* Variables and functions */

__attribute__((used)) static inline void
__nvme_fc_init_hctx(struct blk_mq_hw_ctx *hctx, struct nvme_fc_ctrl *ctrl,
		unsigned int qidx)
{
	struct nvme_fc_queue *queue = &ctrl->queues[qidx];

	hctx->driver_data = queue;
	queue->hctx = hctx;
}