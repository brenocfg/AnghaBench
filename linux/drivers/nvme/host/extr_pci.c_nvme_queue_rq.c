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
struct request {int dummy; } ;
struct nvme_queue {int /*<<< orphan*/  flags; struct nvme_dev* dev; } ;
struct nvme_ns {int dummy; } ;
struct nvme_iod {int npages; scalar_t__ nents; scalar_t__ aborted; } ;
struct nvme_dev {int dummy; } ;
struct nvme_command {int dummy; } ;
struct blk_mq_queue_data {int /*<<< orphan*/  last; struct request* rq; } ;
struct blk_mq_hw_ctx {struct nvme_queue* driver_data; TYPE_1__* queue; } ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_2__ {struct nvme_ns* queuedata; } ;

/* Variables and functions */
 scalar_t__ BLK_STS_IOERR ; 
 scalar_t__ BLK_STS_OK ; 
 int /*<<< orphan*/  NVMEQ_ENABLED ; 
 scalar_t__ blk_integrity_rq (struct request*) ; 
 struct nvme_iod* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  blk_mq_start_request (struct request*) ; 
 scalar_t__ blk_rq_nr_phys_segments (struct request*) ; 
 int /*<<< orphan*/  nvme_cleanup_cmd (struct request*) ; 
 scalar_t__ nvme_map_data (struct nvme_dev*,struct request*,struct nvme_command*) ; 
 scalar_t__ nvme_map_metadata (struct nvme_dev*,struct request*,struct nvme_command*) ; 
 scalar_t__ nvme_setup_cmd (struct nvme_ns*,struct request*,struct nvme_command*) ; 
 int /*<<< orphan*/  nvme_submit_cmd (struct nvme_queue*,struct nvme_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_unmap_data (struct nvme_dev*,struct request*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static blk_status_t nvme_queue_rq(struct blk_mq_hw_ctx *hctx,
			 const struct blk_mq_queue_data *bd)
{
	struct nvme_ns *ns = hctx->queue->queuedata;
	struct nvme_queue *nvmeq = hctx->driver_data;
	struct nvme_dev *dev = nvmeq->dev;
	struct request *req = bd->rq;
	struct nvme_iod *iod = blk_mq_rq_to_pdu(req);
	struct nvme_command cmnd;
	blk_status_t ret;

	iod->aborted = 0;
	iod->npages = -1;
	iod->nents = 0;

	/*
	 * We should not need to do this, but we're still using this to
	 * ensure we can drain requests on a dying queue.
	 */
	if (unlikely(!test_bit(NVMEQ_ENABLED, &nvmeq->flags)))
		return BLK_STS_IOERR;

	ret = nvme_setup_cmd(ns, req, &cmnd);
	if (ret)
		return ret;

	if (blk_rq_nr_phys_segments(req)) {
		ret = nvme_map_data(dev, req, &cmnd);
		if (ret)
			goto out_free_cmd;
	}

	if (blk_integrity_rq(req)) {
		ret = nvme_map_metadata(dev, req, &cmnd);
		if (ret)
			goto out_unmap_data;
	}

	blk_mq_start_request(req);
	nvme_submit_cmd(nvmeq, &cmnd, bd->last);
	return BLK_STS_OK;
out_unmap_data:
	nvme_unmap_data(dev, req);
out_free_cmd:
	nvme_cleanup_cmd(req);
	return ret;
}