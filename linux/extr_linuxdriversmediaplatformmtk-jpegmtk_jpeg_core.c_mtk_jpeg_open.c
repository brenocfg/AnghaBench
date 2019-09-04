#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct video_device {int dummy; } ;
struct mtk_jpeg_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  m2m_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  m2m_ctx; } ;
struct mtk_jpeg_ctx {TYPE_1__ fh; struct mtk_jpeg_dev* jpeg; } ;
struct file {TYPE_1__* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mtk_jpeg_ctx*) ; 
 struct mtk_jpeg_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_jpeg_queue_init ; 
 int /*<<< orphan*/  mtk_jpeg_set_default_params (struct mtk_jpeg_ctx*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_add (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_del (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_fh_init (TYPE_1__*,struct video_device*) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_init (int /*<<< orphan*/ ,struct mtk_jpeg_ctx*,int /*<<< orphan*/ ) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct mtk_jpeg_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int mtk_jpeg_open(struct file *file)
{
	struct mtk_jpeg_dev *jpeg = video_drvdata(file);
	struct video_device *vfd = video_devdata(file);
	struct mtk_jpeg_ctx *ctx;
	int ret = 0;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	if (mutex_lock_interruptible(&jpeg->lock)) {
		ret = -ERESTARTSYS;
		goto free;
	}

	v4l2_fh_init(&ctx->fh, vfd);
	file->private_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	ctx->jpeg = jpeg;
	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(jpeg->m2m_dev, ctx,
					    mtk_jpeg_queue_init);
	if (IS_ERR(ctx->fh.m2m_ctx)) {
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		goto error;
	}

	mtk_jpeg_set_default_params(ctx);
	mutex_unlock(&jpeg->lock);
	return 0;

error:
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_exit(&ctx->fh);
	mutex_unlock(&jpeg->lock);
free:
	kfree(ctx);
	return ret;
}