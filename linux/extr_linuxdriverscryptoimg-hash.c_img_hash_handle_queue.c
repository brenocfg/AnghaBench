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
struct img_hash_request_ctx {int /*<<< orphan*/  op; } ;
struct img_hash_dev {int flags; int /*<<< orphan*/  dev; struct ahash_request* req; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct crypto_async_request {int /*<<< orphan*/  (* complete ) (struct crypto_async_request*,int) ;} ;
struct ahash_request {int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 int DRIVER_FLAGS_BUSY ; 
 int EINPROGRESS ; 
 int ahash_enqueue_request (int /*<<< orphan*/ *,struct ahash_request*) ; 
 struct ahash_request* ahash_request_cast (struct crypto_async_request*) ; 
 struct img_hash_request_ctx* ahash_request_ctx (struct ahash_request*) ; 
 struct crypto_async_request* crypto_dequeue_request (int /*<<< orphan*/ *) ; 
 struct crypto_async_request* crypto_get_backlog (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_hash_finish_req (struct ahash_request*,int) ; 
 int img_hash_hw_init (struct img_hash_dev*) ; 
 int img_hash_process_data (struct img_hash_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct crypto_async_request*,int) ; 

__attribute__((used)) static int img_hash_handle_queue(struct img_hash_dev *hdev,
				 struct ahash_request *req)
{
	struct crypto_async_request *async_req, *backlog;
	struct img_hash_request_ctx *ctx;
	unsigned long flags;
	int err = 0, res = 0;

	spin_lock_irqsave(&hdev->lock, flags);

	if (req)
		res = ahash_enqueue_request(&hdev->queue, req);

	if (DRIVER_FLAGS_BUSY & hdev->flags) {
		spin_unlock_irqrestore(&hdev->lock, flags);
		return res;
	}

	backlog = crypto_get_backlog(&hdev->queue);
	async_req = crypto_dequeue_request(&hdev->queue);
	if (async_req)
		hdev->flags |= DRIVER_FLAGS_BUSY;

	spin_unlock_irqrestore(&hdev->lock, flags);

	if (!async_req)
		return res;

	if (backlog)
		backlog->complete(backlog, -EINPROGRESS);

	req = ahash_request_cast(async_req);
	hdev->req = req;

	ctx = ahash_request_ctx(req);

	dev_info(hdev->dev, "processing req, op: %lu, bytes: %d\n",
		 ctx->op, req->nbytes);

	err = img_hash_hw_init(hdev);

	if (!err)
		err = img_hash_process_data(hdev);

	if (err != -EINPROGRESS) {
		/* done_task will not finish so do it here */
		img_hash_finish_req(req, err);
	}
	return res;
}