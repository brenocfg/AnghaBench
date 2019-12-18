#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct g2d_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  mutex; int /*<<< orphan*/  m2m_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ctrl_handler; int /*<<< orphan*/  m2m_ctx; } ;
struct g2d_ctx {int /*<<< orphan*/  ctrl_handler; TYPE_1__ fh; void* out; void* in; struct g2d_dev* dev; } ;
struct file {TYPE_1__* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 void* def_frame ; 
 int /*<<< orphan*/  g2d_setup_ctrls (struct g2d_ctx*) ; 
 int /*<<< orphan*/  kfree (struct g2d_ctx*) ; 
 struct g2d_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_init ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_add (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_init (int /*<<< orphan*/ ,struct g2d_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct g2d_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int g2d_open(struct file *file)
{
	struct g2d_dev *dev = video_drvdata(file);
	struct g2d_ctx *ctx = NULL;
	int ret = 0;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;
	ctx->dev = dev;
	/* Set default formats */
	ctx->in		= def_frame;
	ctx->out	= def_frame;

	if (mutex_lock_interruptible(&dev->mutex)) {
		kfree(ctx);
		return -ERESTARTSYS;
	}
	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->m2m_dev, ctx, &queue_init);
	if (IS_ERR(ctx->fh.m2m_ctx)) {
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		mutex_unlock(&dev->mutex);
		kfree(ctx);
		return ret;
	}
	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->private_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	g2d_setup_ctrls(ctx);

	/* Write the default values to the ctx struct */
	v4l2_ctrl_handler_setup(&ctx->ctrl_handler);

	ctx->fh.ctrl_handler = &ctx->ctrl_handler;
	mutex_unlock(&dev->mutex);

	v4l2_info(&dev->v4l2_dev, "instance opened\n");
	return 0;
}