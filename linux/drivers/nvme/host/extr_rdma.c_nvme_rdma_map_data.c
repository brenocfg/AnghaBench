#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct request {int /*<<< orphan*/  q; } ;
struct TYPE_9__ {int /*<<< orphan*/  sgl; } ;
struct nvme_rdma_request {int num_sge; TYPE_4__ sg_table; int /*<<< orphan*/  nents; int /*<<< orphan*/  first_sgl; int /*<<< orphan*/  ref; } ;
struct nvme_rdma_queue {TYPE_2__* ctrl; struct nvme_rdma_device* device; } ;
struct nvme_rdma_device {int num_inline_segments; TYPE_3__* pd; struct ib_device* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct nvme_command {TYPE_1__ common; } ;
struct ib_device {int dummy; } ;
struct TYPE_8__ {int flags; } ;
struct TYPE_7__ {scalar_t__ use_inline_data; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int IB_PD_UNSAFE_GLOBAL_RKEY ; 
 int /*<<< orphan*/  NVME_CMD_SGL_METABUF ; 
 int /*<<< orphan*/  SG_CHUNK_SIZE ; 
 scalar_t__ WRITE ; 
 struct nvme_rdma_request* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  blk_rq_map_sg (int /*<<< orphan*/ ,struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_nr_phys_segments (struct request*) ; 
 scalar_t__ blk_rq_payload_bytes (struct request*) ; 
 int ib_dma_map_sg (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_unmap_sg (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvme_rdma_inline_data_size (struct nvme_rdma_queue*) ; 
 int nvme_rdma_map_sg_fr (struct nvme_rdma_queue*,struct nvme_rdma_request*,struct nvme_command*,int) ; 
 int nvme_rdma_map_sg_inline (struct nvme_rdma_queue*,struct nvme_rdma_request*,struct nvme_command*,int) ; 
 int nvme_rdma_map_sg_single (struct nvme_rdma_queue*,struct nvme_rdma_request*,struct nvme_command*) ; 
 scalar_t__ nvme_rdma_queue_idx (struct nvme_rdma_queue*) ; 
 int nvme_rdma_set_sg_null (struct nvme_command*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  rq_dma_dir (struct request*) ; 
 int sg_alloc_table_chained (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_free_table_chained (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nvme_rdma_map_data(struct nvme_rdma_queue *queue,
		struct request *rq, struct nvme_command *c)
{
	struct nvme_rdma_request *req = blk_mq_rq_to_pdu(rq);
	struct nvme_rdma_device *dev = queue->device;
	struct ib_device *ibdev = dev->dev;
	int count, ret;

	req->num_sge = 1;
	refcount_set(&req->ref, 2); /* send and recv completions */

	c->common.flags |= NVME_CMD_SGL_METABUF;

	if (!blk_rq_nr_phys_segments(rq))
		return nvme_rdma_set_sg_null(c);

	req->sg_table.sgl = req->first_sgl;
	ret = sg_alloc_table_chained(&req->sg_table,
			blk_rq_nr_phys_segments(rq), req->sg_table.sgl,
			SG_CHUNK_SIZE);
	if (ret)
		return -ENOMEM;

	req->nents = blk_rq_map_sg(rq->q, rq, req->sg_table.sgl);

	count = ib_dma_map_sg(ibdev, req->sg_table.sgl, req->nents,
			      rq_dma_dir(rq));
	if (unlikely(count <= 0)) {
		ret = -EIO;
		goto out_free_table;
	}

	if (count <= dev->num_inline_segments) {
		if (rq_data_dir(rq) == WRITE && nvme_rdma_queue_idx(queue) &&
		    queue->ctrl->use_inline_data &&
		    blk_rq_payload_bytes(rq) <=
				nvme_rdma_inline_data_size(queue)) {
			ret = nvme_rdma_map_sg_inline(queue, req, c, count);
			goto out;
		}

		if (count == 1 && dev->pd->flags & IB_PD_UNSAFE_GLOBAL_RKEY) {
			ret = nvme_rdma_map_sg_single(queue, req, c);
			goto out;
		}
	}

	ret = nvme_rdma_map_sg_fr(queue, req, c, count);
out:
	if (unlikely(ret))
		goto out_unmap_sg;

	return 0;

out_unmap_sg:
	ib_dma_unmap_sg(ibdev, req->sg_table.sgl, req->nents, rq_dma_dir(rq));
out_free_table:
	sg_free_table_chained(&req->sg_table, SG_CHUNK_SIZE);
	return ret;
}