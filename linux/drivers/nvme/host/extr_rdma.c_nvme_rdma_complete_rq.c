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
struct request {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma; } ;
struct nvme_rdma_request {TYPE_2__ sqe; struct nvme_rdma_queue* queue; } ;
struct nvme_rdma_queue {TYPE_1__* device; } ;
struct nvme_command {int dummy; } ;
struct ib_device {int dummy; } ;
struct TYPE_3__ {struct ib_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 struct nvme_rdma_request* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  ib_dma_unmap_single (struct ib_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_complete_rq (struct request*) ; 
 int /*<<< orphan*/  nvme_rdma_unmap_data (struct nvme_rdma_queue*,struct request*) ; 

__attribute__((used)) static void nvme_rdma_complete_rq(struct request *rq)
{
	struct nvme_rdma_request *req = blk_mq_rq_to_pdu(rq);
	struct nvme_rdma_queue *queue = req->queue;
	struct ib_device *ibdev = queue->device->dev;

	nvme_rdma_unmap_data(queue, rq);
	ib_dma_unmap_single(ibdev, req->sqe.dma, sizeof(struct nvme_command),
			    DMA_TO_DEVICE);
	nvme_complete_rq(rq);
}