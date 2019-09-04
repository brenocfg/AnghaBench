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
struct hifn_device {scalar_t__ started; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct crypto_async_request {int /*<<< orphan*/  (* complete ) (struct crypto_async_request*,int /*<<< orphan*/ ) ;} ;
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 scalar_t__ HIFN_QUEUE_LENGTH ; 
 struct ablkcipher_request* ablkcipher_request_cast (struct crypto_async_request*) ; 
 struct crypto_async_request* crypto_dequeue_request (int /*<<< orphan*/ *) ; 
 struct crypto_async_request* crypto_get_backlog (int /*<<< orphan*/ *) ; 
 int hifn_handle_req (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct crypto_async_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hifn_process_queue(struct hifn_device *dev)
{
	struct crypto_async_request *async_req, *backlog;
	struct ablkcipher_request *req;
	unsigned long flags;
	int err = 0;

	while (dev->started < HIFN_QUEUE_LENGTH) {
		spin_lock_irqsave(&dev->lock, flags);
		backlog = crypto_get_backlog(&dev->queue);
		async_req = crypto_dequeue_request(&dev->queue);
		spin_unlock_irqrestore(&dev->lock, flags);

		if (!async_req)
			break;

		if (backlog)
			backlog->complete(backlog, -EINPROGRESS);

		req = ablkcipher_request_cast(async_req);

		err = hifn_handle_req(req);
		if (err)
			break;
	}

	return err;
}