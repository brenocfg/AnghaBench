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
struct TYPE_3__ {int /*<<< orphan*/  sgl; } ;
struct nvme_rdma_request {TYPE_1__ sg_table; int /*<<< orphan*/  nents; int /*<<< orphan*/ * mr; } ;
struct nvme_rdma_queue {TYPE_2__* qp; struct nvme_rdma_device* device; } ;
struct nvme_rdma_device {struct ib_device* dev; } ;
struct ib_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rdma_mrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  SG_CHUNK_SIZE ; 
 struct nvme_rdma_request* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  blk_rq_nr_phys_segments (struct request*) ; 
 int /*<<< orphan*/  ib_dma_unmap_sg (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_mr_pool_put (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_cleanup_cmd (struct request*) ; 
 int /*<<< orphan*/  rq_dma_dir (struct request*) ; 
 int /*<<< orphan*/  sg_free_table_chained (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvme_rdma_unmap_data(struct nvme_rdma_queue *queue,
		struct request *rq)
{
	struct nvme_rdma_request *req = blk_mq_rq_to_pdu(rq);
	struct nvme_rdma_device *dev = queue->device;
	struct ib_device *ibdev = dev->dev;

	if (!blk_rq_nr_phys_segments(rq))
		return;

	if (req->mr) {
		ib_mr_pool_put(queue->qp, &queue->qp->rdma_mrs, req->mr);
		req->mr = NULL;
	}

	ib_dma_unmap_sg(ibdev, req->sg_table.sgl, req->nents, rq_dma_dir(rq));

	nvme_cleanup_cmd(rq);
	sg_free_table_chained(&req->sg_table, SG_CHUNK_SIZE);
}