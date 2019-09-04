#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct file {TYPE_2__* private_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  vdev; } ;
struct bdisp_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  state; TYPE_1__ m2m; } ;
struct TYPE_7__ {int /*<<< orphan*/  m2m_ctx; int /*<<< orphan*/ * ctrl_handler; } ;
struct bdisp_ctx {TYPE_2__ fh; void* dst; void* src; int /*<<< orphan*/  ctrl_handler; struct bdisp_dev* bdisp_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_M2M_OPEN ; 
 int bdisp_ctrls_create (struct bdisp_ctx*) ; 
 int /*<<< orphan*/  bdisp_ctrls_delete (struct bdisp_ctx*) ; 
 void* bdisp_dflt_fmt ; 
 scalar_t__ bdisp_hw_alloc_nodes (struct bdisp_ctx*) ; 
 int /*<<< orphan*/  bdisp_hw_free_nodes (struct bdisp_ctx*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct bdisp_ctx*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct bdisp_ctx*) ; 
 struct bdisp_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_init ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_add (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_fh_del (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_fh_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_init (int /*<<< orphan*/ ,struct bdisp_ctx*,int /*<<< orphan*/ ) ; 
 struct bdisp_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int bdisp_open(struct file *file)
{
	struct bdisp_dev *bdisp = video_drvdata(file);
	struct bdisp_ctx *ctx = NULL;
	int ret;

	if (mutex_lock_interruptible(&bdisp->lock))
		return -ERESTARTSYS;

	/* Allocate memory for both context and node */
	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx) {
		ret = -ENOMEM;
		goto unlock;
	}
	ctx->bdisp_dev = bdisp;

	if (bdisp_hw_alloc_nodes(ctx)) {
		dev_err(bdisp->dev, "no memory for nodes\n");
		ret = -ENOMEM;
		goto mem_ctx;
	}

	v4l2_fh_init(&ctx->fh, bdisp->m2m.vdev);

	ret = bdisp_ctrls_create(ctx);
	if (ret) {
		dev_err(bdisp->dev, "Failed to create control\n");
		goto error_fh;
	}

	/* Use separate control handler per file handle */
	ctx->fh.ctrl_handler = &ctx->ctrl_handler;
	file->private_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	/* Default format */
	ctx->src = bdisp_dflt_fmt;
	ctx->dst = bdisp_dflt_fmt;

	/* Setup the device context for mem2mem mode. */
	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(bdisp->m2m.m2m_dev, ctx,
					    queue_init);
	if (IS_ERR(ctx->fh.m2m_ctx)) {
		dev_err(bdisp->dev, "Failed to initialize m2m context\n");
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		goto error_ctrls;
	}

	bdisp->m2m.refcnt++;
	set_bit(ST_M2M_OPEN, &bdisp->state);

	dev_dbg(bdisp->dev, "driver opened, ctx = 0x%p\n", ctx);

	mutex_unlock(&bdisp->lock);

	return 0;

error_ctrls:
	bdisp_ctrls_delete(ctx);
	v4l2_fh_del(&ctx->fh);
error_fh:
	v4l2_fh_exit(&ctx->fh);
	bdisp_hw_free_nodes(ctx);
mem_ctx:
	kfree(ctx);
unlock:
	mutex_unlock(&bdisp->lock);

	return ret;
}