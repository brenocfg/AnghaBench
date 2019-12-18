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
typedef  int /*<<< orphan*/  u32 ;
struct fastrpc_user {int /*<<< orphan*/  lock; int /*<<< orphan*/  pending; int /*<<< orphan*/  tgid; struct fastrpc_channel_ctx* cctx; } ;
struct fastrpc_invoke_ctx {int retval; int ctxid; struct fastrpc_invoke_ctx* olaps; struct fastrpc_invoke_ctx* maps; int /*<<< orphan*/  node; int /*<<< orphan*/  refcount; int /*<<< orphan*/  put_work; int /*<<< orphan*/  work; struct fastrpc_channel_ctx* cctx; int /*<<< orphan*/  tgid; int /*<<< orphan*/  pid; int /*<<< orphan*/  sc; struct fastrpc_invoke_args* args; scalar_t__ nscalars; scalar_t__ nbufs; struct fastrpc_user* fl; } ;
struct fastrpc_invoke_args {int dummy; } ;
struct fastrpc_channel_ctx {int /*<<< orphan*/  lock; int /*<<< orphan*/  ctx_idr; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct fastrpc_invoke_ctx* ERR_PTR (int) ; 
 int /*<<< orphan*/  FASTRPC_CTX_MAX ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ REMOTE_SCALARS_INBUFS (int /*<<< orphan*/ ) ; 
 scalar_t__ REMOTE_SCALARS_LENGTH (int /*<<< orphan*/ ) ; 
 scalar_t__ REMOTE_SCALARS_OUTBUFS (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  fastrpc_channel_ctx_get (struct fastrpc_channel_ctx*) ; 
 int /*<<< orphan*/  fastrpc_channel_ctx_put (struct fastrpc_channel_ctx*) ; 
 int /*<<< orphan*/  fastrpc_context_put_wq ; 
 int /*<<< orphan*/  fastrpc_get_buff_overlaps (struct fastrpc_invoke_ctx*) ; 
 int idr_alloc_cyclic (int /*<<< orphan*/ *,struct fastrpc_invoke_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 void* kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fastrpc_invoke_ctx*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct fastrpc_invoke_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct fastrpc_invoke_ctx *fastrpc_context_alloc(
			struct fastrpc_user *user, u32 kernel, u32 sc,
			struct fastrpc_invoke_args *args)
{
	struct fastrpc_channel_ctx *cctx = user->cctx;
	struct fastrpc_invoke_ctx *ctx = NULL;
	unsigned long flags;
	int ret;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&ctx->node);
	ctx->fl = user;
	ctx->nscalars = REMOTE_SCALARS_LENGTH(sc);
	ctx->nbufs = REMOTE_SCALARS_INBUFS(sc) +
		     REMOTE_SCALARS_OUTBUFS(sc);

	if (ctx->nscalars) {
		ctx->maps = kcalloc(ctx->nscalars,
				    sizeof(*ctx->maps), GFP_KERNEL);
		if (!ctx->maps) {
			kfree(ctx);
			return ERR_PTR(-ENOMEM);
		}
		ctx->olaps = kcalloc(ctx->nscalars,
				    sizeof(*ctx->olaps), GFP_KERNEL);
		if (!ctx->olaps) {
			kfree(ctx->maps);
			kfree(ctx);
			return ERR_PTR(-ENOMEM);
		}
		ctx->args = args;
		fastrpc_get_buff_overlaps(ctx);
	}

	/* Released in fastrpc_context_put() */
	fastrpc_channel_ctx_get(cctx);

	ctx->sc = sc;
	ctx->retval = -1;
	ctx->pid = current->pid;
	ctx->tgid = user->tgid;
	ctx->cctx = cctx;
	init_completion(&ctx->work);
	INIT_WORK(&ctx->put_work, fastrpc_context_put_wq);

	spin_lock(&user->lock);
	list_add_tail(&ctx->node, &user->pending);
	spin_unlock(&user->lock);

	spin_lock_irqsave(&cctx->lock, flags);
	ret = idr_alloc_cyclic(&cctx->ctx_idr, ctx, 1,
			       FASTRPC_CTX_MAX, GFP_ATOMIC);
	if (ret < 0) {
		spin_unlock_irqrestore(&cctx->lock, flags);
		goto err_idr;
	}
	ctx->ctxid = ret << 4;
	spin_unlock_irqrestore(&cctx->lock, flags);

	kref_init(&ctx->refcount);

	return ctx;
err_idr:
	spin_lock(&user->lock);
	list_del(&ctx->node);
	spin_unlock(&user->lock);
	fastrpc_channel_ctx_put(cctx);
	kfree(ctx->maps);
	kfree(ctx->olaps);
	kfree(ctx);

	return ERR_PTR(ret);
}