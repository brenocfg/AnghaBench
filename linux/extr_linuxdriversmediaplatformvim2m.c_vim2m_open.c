#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vim2m_dev {int /*<<< orphan*/  dev_mutex; int /*<<< orphan*/  num_inst; int /*<<< orphan*/  m2m_dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  m2m_ctx; struct v4l2_ctrl_handler* ctrl_handler; } ;
struct v4l2_ctrl_handler {int error; } ;
struct vim2m_ctx {TYPE_2__ fh; int /*<<< orphan*/  colorspace; TYPE_1__* q_data; struct v4l2_ctrl_handler hdl; struct vim2m_dev* dev; } ;
struct file {TYPE_2__* private_data; } ;
struct TYPE_8__ {int depth; } ;
struct TYPE_6__ {int width; int height; int sizeimage; TYPE_5__* fmt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_REC709 ; 
 size_t V4L2_M2M_DST ; 
 size_t V4L2_M2M_SRC ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (struct vim2m_dev*,char*,struct vim2m_ctx*,int /*<<< orphan*/ ) ; 
 TYPE_5__* formats ; 
 int /*<<< orphan*/  kfree (struct vim2m_ctx*) ; 
 struct vim2m_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_init ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_custom (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fh_add (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_fh_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_init (int /*<<< orphan*/ ,struct vim2m_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct vim2m_dev* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vim2m_ctrl_ops ; 
 int /*<<< orphan*/  vim2m_ctrl_trans_num_bufs ; 
 int /*<<< orphan*/  vim2m_ctrl_trans_time_msec ; 

__attribute__((used)) static int vim2m_open(struct file *file)
{
	struct vim2m_dev *dev = video_drvdata(file);
	struct vim2m_ctx *ctx = NULL;
	struct v4l2_ctrl_handler *hdl;
	int rc = 0;

	if (mutex_lock_interruptible(&dev->dev_mutex))
		return -ERESTARTSYS;
	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx) {
		rc = -ENOMEM;
		goto open_unlock;
	}

	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->private_data = &ctx->fh;
	ctx->dev = dev;
	hdl = &ctx->hdl;
	v4l2_ctrl_handler_init(hdl, 4);
	v4l2_ctrl_new_std(hdl, &vim2m_ctrl_ops, V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(hdl, &vim2m_ctrl_ops, V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_custom(hdl, &vim2m_ctrl_trans_time_msec, NULL);
	v4l2_ctrl_new_custom(hdl, &vim2m_ctrl_trans_num_bufs, NULL);
	if (hdl->error) {
		rc = hdl->error;
		v4l2_ctrl_handler_free(hdl);
		kfree(ctx);
		goto open_unlock;
	}
	ctx->fh.ctrl_handler = hdl;
	v4l2_ctrl_handler_setup(hdl);

	ctx->q_data[V4L2_M2M_SRC].fmt = &formats[0];
	ctx->q_data[V4L2_M2M_SRC].width = 640;
	ctx->q_data[V4L2_M2M_SRC].height = 480;
	ctx->q_data[V4L2_M2M_SRC].sizeimage =
		ctx->q_data[V4L2_M2M_SRC].width *
		ctx->q_data[V4L2_M2M_SRC].height *
		(ctx->q_data[V4L2_M2M_SRC].fmt->depth >> 3);
	ctx->q_data[V4L2_M2M_DST] = ctx->q_data[V4L2_M2M_SRC];
	ctx->colorspace = V4L2_COLORSPACE_REC709;

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->m2m_dev, ctx, &queue_init);

	if (IS_ERR(ctx->fh.m2m_ctx)) {
		rc = PTR_ERR(ctx->fh.m2m_ctx);

		v4l2_ctrl_handler_free(hdl);
		v4l2_fh_exit(&ctx->fh);
		kfree(ctx);
		goto open_unlock;
	}

	v4l2_fh_add(&ctx->fh);
	atomic_inc(&dev->num_inst);

	dprintk(dev, "Created instance: %p, m2m_ctx: %p\n",
		ctx, ctx->fh.m2m_ctx);

open_unlock:
	mutex_unlock(&dev->dev_mutex);
	return rc;
}