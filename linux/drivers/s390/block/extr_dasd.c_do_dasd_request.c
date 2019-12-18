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
struct dasd_queue {int /*<<< orphan*/  lock; } ;
struct dasd_device {scalar_t__ state; int features; TYPE_2__* discipline; int /*<<< orphan*/  flags; scalar_t__ stopped; } ;
struct dasd_ccw_req {int /*<<< orphan*/  devlist; int /*<<< orphan*/  blocklist; struct dasd_queue* dq; int /*<<< orphan*/  status; struct request* callback_data; } ;
struct dasd_block {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  ccw_queue; struct dasd_device* base; } ;
struct blk_mq_queue_data {struct request* rq; } ;
struct blk_mq_hw_ctx {struct dasd_queue* driver_data; TYPE_1__* queue; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_4__ {struct dasd_ccw_req* (* build_cp ) (struct dasd_device*,struct dasd_block*,struct request*) ;} ;
struct TYPE_3__ {struct dasd_block* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  DASD_CQR_FILLED ; 
 int DASD_FEATURE_FAILFAST ; 
 int DASD_FEATURE_READONLY ; 
 int /*<<< orphan*/  DASD_FLAG_ABORTALL ; 
 scalar_t__ DASD_STATE_READY ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DBF_ERR ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  PTR_ERR (struct dasd_ccw_req*) ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  blk_mq_start_request (struct request*) ; 
 scalar_t__ blk_noretry_request (struct request*) ; 
 int /*<<< orphan*/  dasd_profile_start (struct dasd_block*,struct dasd_ccw_req*,struct request*) ; 
 int /*<<< orphan*/  dasd_schedule_block_bh (struct dasd_block*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct dasd_ccw_req* stub1 (struct dasd_device*,struct dasd_block*,struct request*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static blk_status_t do_dasd_request(struct blk_mq_hw_ctx *hctx,
				    const struct blk_mq_queue_data *qd)
{
	struct dasd_block *block = hctx->queue->queuedata;
	struct dasd_queue *dq = hctx->driver_data;
	struct request *req = qd->rq;
	struct dasd_device *basedev;
	struct dasd_ccw_req *cqr;
	blk_status_t rc = BLK_STS_OK;

	basedev = block->base;
	spin_lock_irq(&dq->lock);
	if (basedev->state < DASD_STATE_READY) {
		DBF_DEV_EVENT(DBF_ERR, basedev,
			      "device not ready for request %p", req);
		rc = BLK_STS_IOERR;
		goto out;
	}

	/*
	 * if device is stopped do not fetch new requests
	 * except failfast is active which will let requests fail
	 * immediately in __dasd_block_start_head()
	 */
	if (basedev->stopped && !(basedev->features & DASD_FEATURE_FAILFAST)) {
		DBF_DEV_EVENT(DBF_ERR, basedev,
			      "device stopped request %p", req);
		rc = BLK_STS_RESOURCE;
		goto out;
	}

	if (basedev->features & DASD_FEATURE_READONLY &&
	    rq_data_dir(req) == WRITE) {
		DBF_DEV_EVENT(DBF_ERR, basedev,
			      "Rejecting write request %p", req);
		rc = BLK_STS_IOERR;
		goto out;
	}

	if (test_bit(DASD_FLAG_ABORTALL, &basedev->flags) &&
	    (basedev->features & DASD_FEATURE_FAILFAST ||
	     blk_noretry_request(req))) {
		DBF_DEV_EVENT(DBF_ERR, basedev,
			      "Rejecting failfast request %p", req);
		rc = BLK_STS_IOERR;
		goto out;
	}

	cqr = basedev->discipline->build_cp(basedev, block, req);
	if (IS_ERR(cqr)) {
		if (PTR_ERR(cqr) == -EBUSY ||
		    PTR_ERR(cqr) == -ENOMEM ||
		    PTR_ERR(cqr) == -EAGAIN) {
			rc = BLK_STS_RESOURCE;
			goto out;
		}
		DBF_DEV_EVENT(DBF_ERR, basedev,
			      "CCW creation failed (rc=%ld) on request %p",
			      PTR_ERR(cqr), req);
		rc = BLK_STS_IOERR;
		goto out;
	}
	/*
	 *  Note: callback is set to dasd_return_cqr_cb in
	 * __dasd_block_start_head to cover erp requests as well
	 */
	cqr->callback_data = req;
	cqr->status = DASD_CQR_FILLED;
	cqr->dq = dq;

	blk_mq_start_request(req);
	spin_lock(&block->queue_lock);
	list_add_tail(&cqr->blocklist, &block->ccw_queue);
	INIT_LIST_HEAD(&cqr->devlist);
	dasd_profile_start(block, cqr, req);
	dasd_schedule_block_bh(block);
	spin_unlock(&block->queue_lock);

out:
	spin_unlock_irq(&dq->lock);
	return rc;
}