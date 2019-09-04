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
struct qce_device {int result; int /*<<< orphan*/  done_tasklet; int /*<<< orphan*/  lock; struct crypto_async_request* req; int /*<<< orphan*/  queue; } ;
struct crypto_async_request {int /*<<< orphan*/  (* complete ) (struct crypto_async_request*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 struct crypto_async_request* crypto_dequeue_request (int /*<<< orphan*/ *) ; 
 int crypto_enqueue_request (int /*<<< orphan*/ *,struct crypto_async_request*) ; 
 struct crypto_async_request* crypto_get_backlog (int /*<<< orphan*/ *) ; 
 int qce_handle_request (struct crypto_async_request*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct crypto_async_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qce_handle_queue(struct qce_device *qce,
			    struct crypto_async_request *req)
{
	struct crypto_async_request *async_req, *backlog;
	unsigned long flags;
	int ret = 0, err;

	spin_lock_irqsave(&qce->lock, flags);

	if (req)
		ret = crypto_enqueue_request(&qce->queue, req);

	/* busy, do not dequeue request */
	if (qce->req) {
		spin_unlock_irqrestore(&qce->lock, flags);
		return ret;
	}

	backlog = crypto_get_backlog(&qce->queue);
	async_req = crypto_dequeue_request(&qce->queue);
	if (async_req)
		qce->req = async_req;

	spin_unlock_irqrestore(&qce->lock, flags);

	if (!async_req)
		return ret;

	if (backlog) {
		spin_lock_bh(&qce->lock);
		backlog->complete(backlog, -EINPROGRESS);
		spin_unlock_bh(&qce->lock);
	}

	err = qce_handle_request(async_req);
	if (err) {
		qce->result = err;
		tasklet_schedule(&qce->done_tasklet);
	}

	return ret;
}