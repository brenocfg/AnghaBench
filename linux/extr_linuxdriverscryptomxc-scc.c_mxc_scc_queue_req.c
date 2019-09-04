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
struct mxc_scc_ctx {TYPE_1__* scc; } ;
struct crypto_async_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int crypto_enqueue_request (int /*<<< orphan*/ *,struct crypto_async_request*) ; 
 int /*<<< orphan*/  mxc_scc_dequeue_req_unlocked (struct mxc_scc_ctx*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxc_scc_queue_req(struct mxc_scc_ctx *ctx,
			     struct crypto_async_request *req)
{
	int ret;

	spin_lock_bh(&ctx->scc->lock);
	ret = crypto_enqueue_request(&ctx->scc->queue, req);
	spin_unlock_bh(&ctx->scc->lock);

	if (ret != -EINPROGRESS)
		return ret;

	mxc_scc_dequeue_req_unlocked(ctx);

	return -EINPROGRESS;
}