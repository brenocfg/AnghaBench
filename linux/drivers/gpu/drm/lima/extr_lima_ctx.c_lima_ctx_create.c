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
typedef  int /*<<< orphan*/  u32 ;
struct lima_device {scalar_t__ pipe; } ;
struct lima_ctx_mgr {int /*<<< orphan*/  handles; } ;
struct lima_ctx {scalar_t__ context; int /*<<< orphan*/  guilty; int /*<<< orphan*/  refcnt; struct lima_device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct lima_ctx*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct lima_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int lima_pipe_num ; 
 int /*<<< orphan*/  lima_sched_context_fini (scalar_t__,scalar_t__) ; 
 int lima_sched_context_init (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int xa_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct lima_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_limit_32b ; 

int lima_ctx_create(struct lima_device *dev, struct lima_ctx_mgr *mgr, u32 *id)
{
	struct lima_ctx *ctx;
	int i, err;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;
	ctx->dev = dev;
	kref_init(&ctx->refcnt);

	for (i = 0; i < lima_pipe_num; i++) {
		err = lima_sched_context_init(dev->pipe + i, ctx->context + i, &ctx->guilty);
		if (err)
			goto err_out0;
	}

	err = xa_alloc(&mgr->handles, id, ctx, xa_limit_32b, GFP_KERNEL);
	if (err < 0)
		goto err_out0;

	return 0;

err_out0:
	for (i--; i >= 0; i--)
		lima_sched_context_fini(dev->pipe + i, ctx->context + i);
	kfree(ctx);
	return err;
}