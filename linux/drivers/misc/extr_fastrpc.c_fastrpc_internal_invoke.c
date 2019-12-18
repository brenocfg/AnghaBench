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
struct fastrpc_user {TYPE_2__* sctx; int /*<<< orphan*/  lock; TYPE_1__* cctx; } ;
struct fastrpc_invoke_ctx {int retval; int /*<<< orphan*/  node; scalar_t__ nscalars; int /*<<< orphan*/  work; } ;
struct fastrpc_invoke_args {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  rpdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPIPE ; 
 scalar_t__ IS_ERR (struct fastrpc_invoke_ctx*) ; 
 int PTR_ERR (struct fastrpc_invoke_ctx*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  dma_wmb () ; 
 struct fastrpc_invoke_ctx* fastrpc_context_alloc (struct fastrpc_user*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fastrpc_invoke_args*) ; 
 int /*<<< orphan*/  fastrpc_context_put (struct fastrpc_invoke_ctx*) ; 
 int fastrpc_get_args (int /*<<< orphan*/ ,struct fastrpc_invoke_ctx*) ; 
 int fastrpc_invoke_send (TYPE_2__*,struct fastrpc_invoke_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fastrpc_put_args (struct fastrpc_invoke_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fastrpc_internal_invoke(struct fastrpc_user *fl,  u32 kernel,
				   u32 handle, u32 sc,
				   struct fastrpc_invoke_args *args)
{
	struct fastrpc_invoke_ctx *ctx = NULL;
	int err = 0;

	if (!fl->sctx)
		return -EINVAL;

	if (!fl->cctx->rpdev)
		return -EPIPE;

	ctx = fastrpc_context_alloc(fl, kernel, sc, args);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	if (ctx->nscalars) {
		err = fastrpc_get_args(kernel, ctx);
		if (err)
			goto bail;
	}

	/* make sure that all CPU memory writes are seen by DSP */
	dma_wmb();
	/* Send invoke buffer to remote dsp */
	err = fastrpc_invoke_send(fl->sctx, ctx, kernel, handle);
	if (err)
		goto bail;

	/* Wait for remote dsp to respond or time out */
	err = wait_for_completion_interruptible(&ctx->work);
	if (err)
		goto bail;

	/* Check the response from remote dsp */
	err = ctx->retval;
	if (err)
		goto bail;

	if (ctx->nscalars) {
		/* make sure that all memory writes by DSP are seen by CPU */
		dma_rmb();
		/* populate all the output buffers with results */
		err = fastrpc_put_args(ctx, kernel);
		if (err)
			goto bail;
	}

bail:
	/* We are done with this compute context, remove it from pending list */
	spin_lock(&fl->lock);
	list_del(&ctx->node);
	spin_unlock(&fl->lock);
	fastrpc_context_put(ctx);

	if (err)
		dev_dbg(fl->sctx->dev, "Error: Invoke Failed %d\n", err);

	return err;
}