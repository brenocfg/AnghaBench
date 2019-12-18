#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct request {scalar_t__ tag; } ;
struct TYPE_11__ {int /*<<< orphan*/  done; } ;
struct nvme_rdma_qe {int /*<<< orphan*/  dma; TYPE_4__ cqe; struct nvme_command* data; } ;
struct TYPE_12__ {int /*<<< orphan*/  wr; } ;
struct nvme_rdma_request {struct nvme_rdma_qe sqe; TYPE_5__ reg_wr; scalar_t__ mr; int /*<<< orphan*/  num_sge; int /*<<< orphan*/  sge; } ;
struct nvme_rdma_queue {TYPE_3__* ctrl; TYPE_2__* device; int /*<<< orphan*/  flags; } ;
struct nvme_ns {int dummy; } ;
struct nvme_command {int dummy; } ;
struct ib_device {int dummy; } ;
struct blk_mq_queue_data {struct request* rq; } ;
struct blk_mq_hw_ctx {struct nvme_rdma_queue* driver_data; TYPE_1__* queue; } ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_13__ {int /*<<< orphan*/  device; } ;
struct TYPE_10__ {TYPE_6__ ctrl; } ;
struct TYPE_9__ {struct ib_device* dev; } ;
struct TYPE_8__ {struct nvme_ns* queuedata; } ;

/* Variables and functions */
 scalar_t__ BLK_STS_IOERR ; 
 scalar_t__ BLK_STS_OK ; 
 scalar_t__ BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NVME_RDMA_Q_LIVE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct nvme_rdma_request* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  blk_mq_start_request (struct request*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ib_dma_map_single (struct ib_device*,struct nvme_command*,int,int /*<<< orphan*/ ) ; 
 int ib_dma_mapping_error (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_cpu (struct ib_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_device (struct ib_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_unmap_single (struct ib_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_cleanup_cmd (struct request*) ; 
 int nvme_rdma_map_data (struct nvme_rdma_queue*,struct request*,struct nvme_command*) ; 
 int nvme_rdma_post_send (struct nvme_rdma_queue*,struct nvme_rdma_qe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_rdma_send_done ; 
 int /*<<< orphan*/  nvme_rdma_unmap_data (struct nvme_rdma_queue*,struct request*) ; 
 scalar_t__ nvme_setup_cmd (struct nvme_ns*,struct request*,struct nvme_command*) ; 
 int /*<<< orphan*/  nvmf_check_ready (TYPE_6__*,struct request*,int) ; 
 scalar_t__ nvmf_fail_nonready_command (TYPE_6__*,struct request*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static blk_status_t nvme_rdma_queue_rq(struct blk_mq_hw_ctx *hctx,
		const struct blk_mq_queue_data *bd)
{
	struct nvme_ns *ns = hctx->queue->queuedata;
	struct nvme_rdma_queue *queue = hctx->driver_data;
	struct request *rq = bd->rq;
	struct nvme_rdma_request *req = blk_mq_rq_to_pdu(rq);
	struct nvme_rdma_qe *sqe = &req->sqe;
	struct nvme_command *c = sqe->data;
	struct ib_device *dev;
	bool queue_ready = test_bit(NVME_RDMA_Q_LIVE, &queue->flags);
	blk_status_t ret;
	int err;

	WARN_ON_ONCE(rq->tag < 0);

	if (!nvmf_check_ready(&queue->ctrl->ctrl, rq, queue_ready))
		return nvmf_fail_nonready_command(&queue->ctrl->ctrl, rq);

	dev = queue->device->dev;

	req->sqe.dma = ib_dma_map_single(dev, req->sqe.data,
					 sizeof(struct nvme_command),
					 DMA_TO_DEVICE);
	err = ib_dma_mapping_error(dev, req->sqe.dma);
	if (unlikely(err))
		return BLK_STS_RESOURCE;

	ib_dma_sync_single_for_cpu(dev, sqe->dma,
			sizeof(struct nvme_command), DMA_TO_DEVICE);

	ret = nvme_setup_cmd(ns, rq, c);
	if (ret)
		goto unmap_qe;

	blk_mq_start_request(rq);

	err = nvme_rdma_map_data(queue, rq, c);
	if (unlikely(err < 0)) {
		dev_err(queue->ctrl->ctrl.device,
			     "Failed to map data (%d)\n", err);
		nvme_cleanup_cmd(rq);
		goto err;
	}

	sqe->cqe.done = nvme_rdma_send_done;

	ib_dma_sync_single_for_device(dev, sqe->dma,
			sizeof(struct nvme_command), DMA_TO_DEVICE);

	err = nvme_rdma_post_send(queue, sqe, req->sge, req->num_sge,
			req->mr ? &req->reg_wr.wr : NULL);
	if (unlikely(err)) {
		nvme_rdma_unmap_data(queue, rq);
		goto err;
	}

	return BLK_STS_OK;

err:
	if (err == -ENOMEM || err == -EAGAIN)
		ret = BLK_STS_RESOURCE;
	else
		ret = BLK_STS_IOERR;
unmap_qe:
	ib_dma_unmap_single(dev, req->sqe.dma, sizeof(struct nvme_command),
			    DMA_TO_DEVICE);
	return ret;
}