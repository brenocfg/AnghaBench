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
struct omap_sham_reqctx {scalar_t__ op; int flags; scalar_t__ digcnt; int /*<<< orphan*/  total; } ;
struct omap_sham_dev {int /*<<< orphan*/  dev; TYPE_1__* pdata; struct ahash_request* req; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  queue; } ;
struct crypto_async_request {int /*<<< orphan*/  (* complete ) (struct crypto_async_request*,int) ;} ;
struct ahash_request {int /*<<< orphan*/  nbytes; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* copy_hash ) (struct ahash_request*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  FLAGS_BUSY ; 
 int /*<<< orphan*/  FLAGS_FINUP ; 
 scalar_t__ OP_FINAL ; 
 scalar_t__ OP_UPDATE ; 
 int ahash_enqueue_request (int /*<<< orphan*/ *,struct ahash_request*) ; 
 struct ahash_request* ahash_request_cast (struct crypto_async_request*) ; 
 struct omap_sham_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 struct crypto_async_request* crypto_dequeue_request (int /*<<< orphan*/ *) ; 
 struct crypto_async_request* crypto_get_backlog (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int omap_sham_final_req (struct omap_sham_dev*) ; 
 int /*<<< orphan*/  omap_sham_finish_req (struct ahash_request*,int) ; 
 int omap_sham_hw_init (struct omap_sham_dev*) ; 
 int omap_sham_prepare_request (struct ahash_request*,int) ; 
 int omap_sham_update_req (struct omap_sham_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct crypto_async_request*,int) ; 
 int /*<<< orphan*/  stub2 (struct ahash_request*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_sham_handle_queue(struct omap_sham_dev *dd,
				  struct ahash_request *req)
{
	struct crypto_async_request *async_req, *backlog;
	struct omap_sham_reqctx *ctx;
	unsigned long flags;
	int err = 0, ret = 0;

retry:
	spin_lock_irqsave(&dd->lock, flags);
	if (req)
		ret = ahash_enqueue_request(&dd->queue, req);
	if (test_bit(FLAGS_BUSY, &dd->flags)) {
		spin_unlock_irqrestore(&dd->lock, flags);
		return ret;
	}
	backlog = crypto_get_backlog(&dd->queue);
	async_req = crypto_dequeue_request(&dd->queue);
	if (async_req)
		set_bit(FLAGS_BUSY, &dd->flags);
	spin_unlock_irqrestore(&dd->lock, flags);

	if (!async_req)
		return ret;

	if (backlog)
		backlog->complete(backlog, -EINPROGRESS);

	req = ahash_request_cast(async_req);
	dd->req = req;
	ctx = ahash_request_ctx(req);

	err = omap_sham_prepare_request(req, ctx->op == OP_UPDATE);
	if (err || !ctx->total)
		goto err1;

	dev_dbg(dd->dev, "handling new req, op: %lu, nbytes: %d\n",
						ctx->op, req->nbytes);

	err = omap_sham_hw_init(dd);
	if (err)
		goto err1;

	if (ctx->digcnt)
		/* request has changed - restore hash */
		dd->pdata->copy_hash(req, 0);

	if (ctx->op == OP_UPDATE) {
		err = omap_sham_update_req(dd);
		if (err != -EINPROGRESS && (ctx->flags & BIT(FLAGS_FINUP)))
			/* no final() after finup() */
			err = omap_sham_final_req(dd);
	} else if (ctx->op == OP_FINAL) {
		err = omap_sham_final_req(dd);
	}
err1:
	dev_dbg(dd->dev, "exit, err: %d\n", err);

	if (err != -EINPROGRESS) {
		/* done_task will not finish it, so do it here */
		omap_sham_finish_req(req, err);
		req = NULL;

		/*
		 * Execute next request immediately if there is anything
		 * in queue.
		 */
		goto retry;
	}

	return ret;
}