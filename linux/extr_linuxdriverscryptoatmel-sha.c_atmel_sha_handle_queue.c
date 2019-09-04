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
struct crypto_async_request {int /*<<< orphan*/  tfm; int /*<<< orphan*/  (* complete ) (struct crypto_async_request*,int /*<<< orphan*/ ) ;} ;
struct atmel_sha_dev {int flags; int is_async; int force_complete; struct ahash_request* req; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct atmel_sha_ctx {int (* start ) (struct atmel_sha_dev*) ;} ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int SHA_FLAGS_BUSY ; 
 int ahash_enqueue_request (int /*<<< orphan*/ *,struct ahash_request*) ; 
 struct ahash_request* ahash_request_cast (struct crypto_async_request*) ; 
 struct crypto_async_request* crypto_dequeue_request (int /*<<< orphan*/ *) ; 
 struct crypto_async_request* crypto_get_backlog (int /*<<< orphan*/ *) ; 
 struct atmel_sha_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct crypto_async_request*,int /*<<< orphan*/ ) ; 
 int stub2 (struct atmel_sha_dev*) ; 

__attribute__((used)) static int atmel_sha_handle_queue(struct atmel_sha_dev *dd,
				  struct ahash_request *req)
{
	struct crypto_async_request *async_req, *backlog;
	struct atmel_sha_ctx *ctx;
	unsigned long flags;
	bool start_async;
	int err = 0, ret = 0;

	spin_lock_irqsave(&dd->lock, flags);
	if (req)
		ret = ahash_enqueue_request(&dd->queue, req);

	if (SHA_FLAGS_BUSY & dd->flags) {
		spin_unlock_irqrestore(&dd->lock, flags);
		return ret;
	}

	backlog = crypto_get_backlog(&dd->queue);
	async_req = crypto_dequeue_request(&dd->queue);
	if (async_req)
		dd->flags |= SHA_FLAGS_BUSY;

	spin_unlock_irqrestore(&dd->lock, flags);

	if (!async_req)
		return ret;

	if (backlog)
		backlog->complete(backlog, -EINPROGRESS);

	ctx = crypto_tfm_ctx(async_req->tfm);

	dd->req = ahash_request_cast(async_req);
	start_async = (dd->req != req);
	dd->is_async = start_async;
	dd->force_complete = false;

	/* WARNING: ctx->start() MAY change dd->is_async. */
	err = ctx->start(dd);
	return (start_async) ? ret : err;
}