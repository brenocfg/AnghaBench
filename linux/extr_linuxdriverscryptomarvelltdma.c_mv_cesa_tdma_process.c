#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mv_cesa_tdma_desc {int flags; scalar_t__ cur_dma; struct mv_cesa_tdma_desc* next; } ;
struct TYPE_3__ {int /*<<< orphan*/ * last; struct mv_cesa_tdma_desc* first; } ;
struct mv_cesa_engine {int /*<<< orphan*/  lock; struct crypto_async_request* req; TYPE_1__ chain; scalar_t__ regs; } ;
struct mv_cesa_ctx {TYPE_2__* ops; } ;
struct crypto_async_request {int /*<<< orphan*/  (* complete ) (struct crypto_async_request*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  tfm; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {int (* process ) (struct crypto_async_request*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* complete ) (struct crypto_async_request*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CESA_SA_INT_ACC0_IDMA_DONE ; 
 scalar_t__ CESA_TDMA_CUR ; 
 int CESA_TDMA_END_OF_REQ ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 struct mv_cesa_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 struct crypto_async_request* mv_cesa_dequeue_req_locked (struct mv_cesa_engine*,struct crypto_async_request**) ; 
 int /*<<< orphan*/  mv_cesa_engine_enqueue_complete_request (struct mv_cesa_engine*,struct crypto_async_request*) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct crypto_async_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct crypto_async_request*) ; 
 int /*<<< orphan*/  stub3 (struct crypto_async_request*,int /*<<< orphan*/ ) ; 

int mv_cesa_tdma_process(struct mv_cesa_engine *engine, u32 status)
{
	struct crypto_async_request *req = NULL;
	struct mv_cesa_tdma_desc *tdma = NULL, *next = NULL;
	dma_addr_t tdma_cur;
	int res = 0;

	tdma_cur = readl(engine->regs + CESA_TDMA_CUR);

	for (tdma = engine->chain.first; tdma; tdma = next) {
		spin_lock_bh(&engine->lock);
		next = tdma->next;
		spin_unlock_bh(&engine->lock);

		if (tdma->flags & CESA_TDMA_END_OF_REQ) {
			struct crypto_async_request *backlog = NULL;
			struct mv_cesa_ctx *ctx;
			u32 current_status;

			spin_lock_bh(&engine->lock);
			/*
			 * if req is NULL, this means we're processing the
			 * request in engine->req.
			 */
			if (!req)
				req = engine->req;
			else
				req = mv_cesa_dequeue_req_locked(engine,
								 &backlog);

			/* Re-chaining to the next request */
			engine->chain.first = tdma->next;
			tdma->next = NULL;

			/* If this is the last request, clear the chain */
			if (engine->chain.first == NULL)
				engine->chain.last  = NULL;
			spin_unlock_bh(&engine->lock);

			ctx = crypto_tfm_ctx(req->tfm);
			current_status = (tdma->cur_dma == tdma_cur) ?
					  status : CESA_SA_INT_ACC0_IDMA_DONE;
			res = ctx->ops->process(req, current_status);
			ctx->ops->complete(req);

			if (res == 0)
				mv_cesa_engine_enqueue_complete_request(engine,
									req);

			if (backlog)
				backlog->complete(backlog, -EINPROGRESS);
		}

		if (res || tdma->cur_dma == tdma_cur)
			break;
	}

	/* Save the last request in error to engine->req, so that the core
	 * knows which request was fautly */
	if (res) {
		spin_lock_bh(&engine->lock);
		engine->req = req;
		spin_unlock_bh(&engine->lock);
	}

	return res;
}