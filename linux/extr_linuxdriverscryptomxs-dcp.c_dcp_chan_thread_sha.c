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
struct dcp_sha_req_ctx {int fini; } ;
struct dcp {int /*<<< orphan*/ * lock; int /*<<< orphan*/ * queue; } ;
struct crypto_async_request {int /*<<< orphan*/  (* complete ) (struct crypto_async_request*,int) ;} ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int DCP_CHAN_HASH_SHA ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 struct ahash_request* ahash_request_cast (struct crypto_async_request*) ; 
 struct dcp_sha_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 struct crypto_async_request* crypto_dequeue_request (int /*<<< orphan*/ *) ; 
 struct crypto_async_request* crypto_get_backlog (int /*<<< orphan*/ *) ; 
 int dcp_sha_req_to_buf (struct crypto_async_request*) ; 
 struct dcp* global_sdcp ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct crypto_async_request*,int) ; 
 int /*<<< orphan*/  stub2 (struct crypto_async_request*,int) ; 

__attribute__((used)) static int dcp_chan_thread_sha(void *data)
{
	struct dcp *sdcp = global_sdcp;
	const int chan = DCP_CHAN_HASH_SHA;

	struct crypto_async_request *backlog;
	struct crypto_async_request *arq;

	struct dcp_sha_req_ctx *rctx;

	struct ahash_request *req;
	int ret, fini;

	while (!kthread_should_stop()) {
		set_current_state(TASK_INTERRUPTIBLE);

		spin_lock(&sdcp->lock[chan]);
		backlog = crypto_get_backlog(&sdcp->queue[chan]);
		arq = crypto_dequeue_request(&sdcp->queue[chan]);
		spin_unlock(&sdcp->lock[chan]);

		if (!backlog && !arq) {
			schedule();
			continue;
		}

		set_current_state(TASK_RUNNING);

		if (backlog)
			backlog->complete(backlog, -EINPROGRESS);

		if (arq) {
			req = ahash_request_cast(arq);
			rctx = ahash_request_ctx(req);

			ret = dcp_sha_req_to_buf(arq);
			fini = rctx->fini;
			arq->complete(arq, ret);
		}
	}

	return 0;
}