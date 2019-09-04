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
struct qce_device {int /*<<< orphan*/  result; int /*<<< orphan*/  lock; struct crypto_async_request* req; } ;
struct crypto_async_request {int /*<<< orphan*/  (* complete ) (struct crypto_async_request*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  qce_handle_queue (struct qce_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct crypto_async_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qce_tasklet_req_done(unsigned long data)
{
	struct qce_device *qce = (struct qce_device *)data;
	struct crypto_async_request *req;
	unsigned long flags;

	spin_lock_irqsave(&qce->lock, flags);
	req = qce->req;
	qce->req = NULL;
	spin_unlock_irqrestore(&qce->lock, flags);

	if (req)
		req->complete(req, qce->result);

	qce_handle_queue(qce, NULL);
}