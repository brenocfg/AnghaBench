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
struct crypto_async_request {int /*<<< orphan*/  (* complete ) (struct crypto_async_request*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int hw_busy; int /*<<< orphan*/  lock; struct crypto_async_request* req; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 struct crypto_async_request* crypto_dequeue_request (int /*<<< orphan*/ *) ; 
 struct crypto_async_request* crypto_get_backlog (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxc_scc_ablkcipher_next (struct mxc_scc_ctx*,struct crypto_async_request*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct crypto_async_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxc_scc_dequeue_req_unlocked(struct mxc_scc_ctx *ctx)
{
	struct crypto_async_request *req, *backlog;

	if (ctx->scc->hw_busy)
		return;

	spin_lock_bh(&ctx->scc->lock);
	backlog = crypto_get_backlog(&ctx->scc->queue);
	req = crypto_dequeue_request(&ctx->scc->queue);
	ctx->scc->req = req;
	ctx->scc->hw_busy = true;
	spin_unlock_bh(&ctx->scc->lock);

	if (!req)
		return;

	if (backlog)
		backlog->complete(backlog, -EINPROGRESS);

	mxc_scc_ablkcipher_next(ctx, req);
}