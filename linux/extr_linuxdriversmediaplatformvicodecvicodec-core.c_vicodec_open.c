#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct video_device {int /*<<< orphan*/  lock; } ;
struct vicodec_dev {int /*<<< orphan*/  dec_lock; int /*<<< orphan*/  dec_dev; int /*<<< orphan*/  enc_lock; int /*<<< orphan*/  enc_dev; struct video_device enc_vfd; } ;
struct TYPE_6__ {void* m2m_ctx; struct v4l2_ctrl_handler* ctrl_handler; } ;
struct v4l2_ctrl_handler {int error; } ;
struct vicodec_ctx {int is_enc; TYPE_2__ fh; int /*<<< orphan*/ * lock; TYPE_1__* q_data; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  ctrl_gop_size; struct v4l2_ctrl_handler hdl; struct vicodec_dev* dev; } ;
struct file {TYPE_2__* private_data; } ;
struct cframe_hdr {int dummy; } ;
struct TYPE_5__ {int width; int height; unsigned int sizeimage; void* fourcc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_GOP_SIZE ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_REC709 ; 
 size_t V4L2_M2M_DST ; 
 size_t V4L2_M2M_SRC ; 
 void* V4L2_PIX_FMT_FWHT ; 
 void* V4L2_PIX_FMT_YUV420 ; 
 int /*<<< orphan*/  kfree (struct vicodec_ctx*) ; 
 struct vicodec_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_init ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_fh_add (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_fh_init (TYPE_2__*,struct video_device*) ; 
 void* v4l2_m2m_ctx_init (int /*<<< orphan*/ ,struct vicodec_ctx*,int /*<<< orphan*/ *) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct vicodec_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vicodec_open(struct file *file)
{
	struct video_device *vfd = video_devdata(file);
	struct vicodec_dev *dev = video_drvdata(file);
	struct vicodec_ctx *ctx = NULL;
	struct v4l2_ctrl_handler *hdl;
	unsigned int size;
	int rc = 0;

	if (mutex_lock_interruptible(vfd->lock))
		return -ERESTARTSYS;
	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx) {
		rc = -ENOMEM;
		goto open_unlock;
	}

	if (vfd == &dev->enc_vfd)
		ctx->is_enc = true;

	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->private_data = &ctx->fh;
	ctx->dev = dev;
	hdl = &ctx->hdl;
	v4l2_ctrl_handler_init(hdl, 4);
	ctx->ctrl_gop_size = v4l2_ctrl_new_std(hdl, NULL,
					       V4L2_CID_MPEG_VIDEO_GOP_SIZE,
					       1, 16, 1, 10);
	if (hdl->error) {
		rc = hdl->error;
		v4l2_ctrl_handler_free(hdl);
		kfree(ctx);
		goto open_unlock;
	}
	ctx->fh.ctrl_handler = hdl;
	v4l2_ctrl_handler_setup(hdl);

	ctx->q_data[V4L2_M2M_SRC].fourcc =
		ctx->is_enc ? V4L2_PIX_FMT_YUV420 : V4L2_PIX_FMT_FWHT;
	ctx->q_data[V4L2_M2M_SRC].width = 1280;
	ctx->q_data[V4L2_M2M_SRC].height = 720;
	size = 1280 * 720 * 3 / 2;
	ctx->q_data[V4L2_M2M_SRC].sizeimage = size;
	ctx->q_data[V4L2_M2M_DST] = ctx->q_data[V4L2_M2M_SRC];
	ctx->q_data[V4L2_M2M_DST].fourcc =
		ctx->is_enc ? V4L2_PIX_FMT_FWHT : V4L2_PIX_FMT_YUV420;
	ctx->colorspace = V4L2_COLORSPACE_REC709;

	size += sizeof(struct cframe_hdr);
	if (ctx->is_enc) {
		ctx->q_data[V4L2_M2M_DST].sizeimage = size;
		ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->enc_dev, ctx,
						    &queue_init);
		ctx->lock = &dev->enc_lock;
	} else {
		ctx->q_data[V4L2_M2M_SRC].sizeimage = size;
		ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->dec_dev, ctx,
						    &queue_init);
		ctx->lock = &dev->dec_lock;
	}

	if (IS_ERR(ctx->fh.m2m_ctx)) {
		rc = PTR_ERR(ctx->fh.m2m_ctx);

		v4l2_ctrl_handler_free(hdl);
		v4l2_fh_exit(&ctx->fh);
		kfree(ctx);
		goto open_unlock;
	}

	v4l2_fh_add(&ctx->fh);

open_unlock:
	mutex_unlock(vfd->lock);
	return rc;
}