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
struct nvme_rdma_queue {int /*<<< orphan*/  ib_cq; } ;
struct blk_mq_hw_ctx {struct nvme_rdma_queue* driver_data; } ;

/* Variables and functions */
 int ib_process_cq_direct (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nvme_rdma_poll(struct blk_mq_hw_ctx *hctx)
{
	struct nvme_rdma_queue *queue = hctx->driver_data;

	return ib_process_cq_direct(queue->ib_cq, -1);
}