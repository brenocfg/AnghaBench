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
struct file {TYPE_1__* private_data; } ;
struct cedrus_dev {int /*<<< orphan*/  dev_mutex; int /*<<< orphan*/  m2m_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct cedrus_ctx {int /*<<< orphan*/  hdl; TYPE_1__ fh; struct cedrus_dev* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int cedrus_init_ctrls (struct cedrus_dev*,struct cedrus_ctx*) ; 
 int /*<<< orphan*/  cedrus_queue_init ; 
 int /*<<< orphan*/  kfree (struct cedrus_ctx*) ; 
 struct cedrus_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_add (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_init (int /*<<< orphan*/ ,struct cedrus_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct cedrus_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int cedrus_open(struct file *file)
{
	struct cedrus_dev *dev = video_drvdata(file);
	struct cedrus_ctx *ctx = NULL;
	int ret;

	if (mutex_lock_interruptible(&dev->dev_mutex))
		return -ERESTARTSYS;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx) {
		mutex_unlock(&dev->dev_mutex);
		return -ENOMEM;
	}

	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->private_data = &ctx->fh;
	ctx->dev = dev;

	ret = cedrus_init_ctrls(dev, ctx);
	if (ret)
		goto err_free;

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->m2m_dev, ctx,
					    &cedrus_queue_init);
	if (IS_ERR(ctx->fh.m2m_ctx)) {
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		goto err_ctrls;
	}

	v4l2_fh_add(&ctx->fh);

	mutex_unlock(&dev->dev_mutex);

	return 0;

err_ctrls:
	v4l2_ctrl_handler_free(&ctx->hdl);
err_free:
	kfree(ctx);
	mutex_unlock(&dev->dev_mutex);

	return ret;
}