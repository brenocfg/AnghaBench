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
struct video_device {int dummy; } ;
struct hantro_func {scalar_t__ id; } ;
struct hantro_dev {int /*<<< orphan*/  m2m_dev; TYPE_1__* variant; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ctrl_handler; void* m2m_ctx; } ;
struct hantro_ctx {TYPE_2__ fh; int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  buf_finish; struct hantro_dev* dev; } ;
struct file {TYPE_2__* private_data; } ;
struct TYPE_6__ {int codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int ENOMEM ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HANTRO_DECODERS ; 
 int HANTRO_ENCODERS ; 
 scalar_t__ IS_ERR (void*) ; 
 scalar_t__ MEDIA_ENT_F_PROC_VIDEO_DECODER ; 
 scalar_t__ MEDIA_ENT_F_PROC_VIDEO_ENCODER ; 
 int PTR_ERR (void*) ; 
 int hantro_ctrls_setup (struct hantro_dev*,struct hantro_ctx*,int) ; 
 int /*<<< orphan*/  hantro_dec_buf_finish ; 
 int /*<<< orphan*/  hantro_enc_buf_finish ; 
 int /*<<< orphan*/  hantro_reset_fmts (struct hantro_ctx*) ; 
 struct hantro_func* hantro_vdev_to_func (struct video_device*) ; 
 int /*<<< orphan*/  kfree (struct hantro_ctx*) ; 
 struct hantro_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_init ; 
 int /*<<< orphan*/  v4l2_fh_add (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_fh_del (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_fh_init (TYPE_2__*,struct video_device*) ; 
 void* v4l2_m2m_ctx_init (int /*<<< orphan*/ ,struct hantro_ctx*,int /*<<< orphan*/ ) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct hantro_dev* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vpu_err (char*) ; 

__attribute__((used)) static int hantro_open(struct file *filp)
{
	struct hantro_dev *vpu = video_drvdata(filp);
	struct video_device *vdev = video_devdata(filp);
	struct hantro_func *func = hantro_vdev_to_func(vdev);
	struct hantro_ctx *ctx;
	int allowed_codecs, ret;

	/*
	 * We do not need any extra locking here, because we operate only
	 * on local data here, except reading few fields from dev, which
	 * do not change through device's lifetime (which is guaranteed by
	 * reference on module from open()) and V4L2 internal objects (such
	 * as vdev and ctx->fh), which have proper locking done in respective
	 * helper functions used here.
	 */

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->dev = vpu;
	if (func->id == MEDIA_ENT_F_PROC_VIDEO_ENCODER) {
		allowed_codecs = vpu->variant->codec & HANTRO_ENCODERS;
		ctx->buf_finish = hantro_enc_buf_finish;
		ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(vpu->m2m_dev, ctx,
						    queue_init);
	} else if (func->id == MEDIA_ENT_F_PROC_VIDEO_DECODER) {
		allowed_codecs = vpu->variant->codec & HANTRO_DECODERS;
		ctx->buf_finish = hantro_dec_buf_finish;
		ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(vpu->m2m_dev, ctx,
						    queue_init);
	} else {
		ctx->fh.m2m_ctx = ERR_PTR(-ENODEV);
	}
	if (IS_ERR(ctx->fh.m2m_ctx)) {
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		kfree(ctx);
		return ret;
	}

	v4l2_fh_init(&ctx->fh, vdev);
	filp->private_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	hantro_reset_fmts(ctx);

	ret = hantro_ctrls_setup(vpu, ctx, allowed_codecs);
	if (ret) {
		vpu_err("Failed to set up controls\n");
		goto err_fh_free;
	}
	ctx->fh.ctrl_handler = &ctx->ctrl_handler;

	return 0;

err_fh_free:
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_exit(&ctx->fh);
	kfree(ctx);
	return ret;
}