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
struct dcp {int /*<<< orphan*/ * lock; int /*<<< orphan*/ * queue; } ;
struct crypto_async_request {int /*<<< orphan*/  (* complete ) (struct crypto_async_request*,int) ;} ;

/* Variables and functions */
 int DCP_CHAN_CRYPTO ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 struct crypto_async_request* crypto_dequeue_request (int /*<<< orphan*/ *) ; 
 struct crypto_async_request* crypto_get_backlog (int /*<<< orphan*/ *) ; 
 struct dcp* global_sdcp ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int mxs_dcp_aes_block_crypt (struct crypto_async_request*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct crypto_async_request*,int) ; 
 int /*<<< orphan*/  stub2 (struct crypto_async_request*,int) ; 

__attribute__((used)) static int dcp_chan_thread_aes(void *data)
{
	struct dcp *sdcp = global_sdcp;
	const int chan = DCP_CHAN_CRYPTO;

	struct crypto_async_request *backlog;
	struct crypto_async_request *arq;

	int ret;

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
			ret = mxs_dcp_aes_block_crypt(arq);
			arq->complete(arq, ret);
		}
	}

	return 0;
}