#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct video_device {int /*<<< orphan*/  lock; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  m2m_dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  m2m_dev; struct video_device vfd; } ;
struct TYPE_13__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  m2m_dev; struct video_device vfd; } ;
struct vicodec_dev {TYPE_1__ stateful_dec; TYPE_2__ stateless_dec; TYPE_5__ stateful_enc; } ;
struct TYPE_14__ {void* m2m_ctx; struct v4l2_ctrl_handler* ctrl_handler; } ;
struct TYPE_12__ {int /*<<< orphan*/  colorspace; } ;
struct v4l2_ctrl_handler {int error; } ;
struct vicodec_ctx {int is_enc; int is_stateless; TYPE_6__ fh; int /*<<< orphan*/ * lock; TYPE_4__ state; TYPE_3__* q_data; struct v4l2_ctrl_handler hdl; struct vicodec_dev* dev; } ;
struct v4l2_fwht_pixfmt_info {int sizeimage_mult; int sizeimage_div; } ;
struct fwht_cframe_hdr {int dummy; } ;
struct file {TYPE_6__* private_data; } ;
struct TYPE_11__ {int coded_width; int coded_height; int visible_width; int visible_height; unsigned int sizeimage; struct v4l2_fwht_pixfmt_info const* info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  V4L2_CID_FWHT_I_FRAME_QP ; 
 int /*<<< orphan*/  V4L2_CID_FWHT_P_FRAME_QP ; 
 int /*<<< orphan*/  V4L2_CID_MIN_BUFFERS_FOR_OUTPUT ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_GOP_SIZE ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_REC709 ; 
 size_t V4L2_M2M_DST ; 
 size_t V4L2_M2M_SRC ; 
 int /*<<< orphan*/  kfree (struct vicodec_ctx*) ; 
 struct vicodec_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 struct v4l2_fwht_pixfmt_info const pixfmt_fwht ; 
 struct v4l2_fwht_pixfmt_info const pixfmt_stateless_fwht ; 
 int /*<<< orphan*/  queue_init ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_custom (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_fh_add (TYPE_6__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_6__*) ; 
 int /*<<< orphan*/  v4l2_fh_init (TYPE_6__*,struct video_device*) ; 
 struct v4l2_fwht_pixfmt_info* v4l2_fwht_get_pixfmt (int /*<<< orphan*/ ) ; 
 void* v4l2_m2m_ctx_init (int /*<<< orphan*/ ,struct vicodec_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vicodec_ctrl_ops ; 
 int /*<<< orphan*/  vicodec_ctrl_stateless_state ; 
 struct video_device* video_devdata (struct file*) ; 
 struct vicodec_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vicodec_open(struct file *file)
{
	const struct v4l2_fwht_pixfmt_info *info = v4l2_fwht_get_pixfmt(0);
	struct video_device *vfd = video_devdata(file);
	struct vicodec_dev *dev = video_drvdata(file);
	struct vicodec_ctx *ctx = NULL;
	struct v4l2_ctrl_handler *hdl;
	unsigned int raw_size;
	unsigned int comp_size;
	int rc = 0;

	if (mutex_lock_interruptible(vfd->lock))
		return -ERESTARTSYS;
	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx) {
		rc = -ENOMEM;
		goto open_unlock;
	}

	if (vfd == &dev->stateful_enc.vfd)
		ctx->is_enc = true;
	else if (vfd == &dev->stateless_dec.vfd)
		ctx->is_stateless = true;

	v4l2_fh_init(&ctx->fh, video_devdata(file));
	file->private_data = &ctx->fh;
	ctx->dev = dev;
	hdl = &ctx->hdl;
	v4l2_ctrl_handler_init(hdl, 5);
	v4l2_ctrl_new_std(hdl, &vicodec_ctrl_ops, V4L2_CID_MPEG_VIDEO_GOP_SIZE,
			  1, 16, 1, 10);
	v4l2_ctrl_new_std(hdl, &vicodec_ctrl_ops, V4L2_CID_FWHT_I_FRAME_QP,
			  1, 31, 1, 20);
	v4l2_ctrl_new_std(hdl, &vicodec_ctrl_ops, V4L2_CID_FWHT_P_FRAME_QP,
			  1, 31, 1, 20);
	if (ctx->is_enc)
		v4l2_ctrl_new_std(hdl, &vicodec_ctrl_ops,
				  V4L2_CID_MIN_BUFFERS_FOR_OUTPUT, 1, 1, 1, 1);
	if (ctx->is_stateless)
		v4l2_ctrl_new_custom(hdl, &vicodec_ctrl_stateless_state, NULL);
	if (hdl->error) {
		rc = hdl->error;
		v4l2_ctrl_handler_free(hdl);
		kfree(ctx);
		goto open_unlock;
	}
	ctx->fh.ctrl_handler = hdl;
	v4l2_ctrl_handler_setup(hdl);

	if (ctx->is_enc)
		ctx->q_data[V4L2_M2M_SRC].info = info;
	else if (ctx->is_stateless)
		ctx->q_data[V4L2_M2M_SRC].info = &pixfmt_stateless_fwht;
	else
		ctx->q_data[V4L2_M2M_SRC].info = &pixfmt_fwht;
	ctx->q_data[V4L2_M2M_SRC].coded_width = 1280;
	ctx->q_data[V4L2_M2M_SRC].coded_height = 720;
	ctx->q_data[V4L2_M2M_SRC].visible_width = 1280;
	ctx->q_data[V4L2_M2M_SRC].visible_height = 720;
	raw_size = 1280 * 720 * info->sizeimage_mult / info->sizeimage_div;
	comp_size = 1280 * 720 * pixfmt_fwht.sizeimage_mult /
				 pixfmt_fwht.sizeimage_div;
	if (ctx->is_enc)
		ctx->q_data[V4L2_M2M_SRC].sizeimage = raw_size;
	else if (ctx->is_stateless)
		ctx->q_data[V4L2_M2M_SRC].sizeimage = comp_size;
	else
		ctx->q_data[V4L2_M2M_SRC].sizeimage =
			comp_size + sizeof(struct fwht_cframe_hdr);
	ctx->q_data[V4L2_M2M_DST] = ctx->q_data[V4L2_M2M_SRC];
	if (ctx->is_enc) {
		ctx->q_data[V4L2_M2M_DST].info = &pixfmt_fwht;
		ctx->q_data[V4L2_M2M_DST].sizeimage =
			comp_size + sizeof(struct fwht_cframe_hdr);
	} else {
		ctx->q_data[V4L2_M2M_DST].info = info;
		ctx->q_data[V4L2_M2M_DST].sizeimage = raw_size;
	}

	ctx->state.colorspace = V4L2_COLORSPACE_REC709;

	if (ctx->is_enc) {
		ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->stateful_enc.m2m_dev,
						    ctx, &queue_init);
		ctx->lock = &dev->stateful_enc.lock;
	} else if (ctx->is_stateless) {
		ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->stateless_dec.m2m_dev,
						    ctx, &queue_init);
		ctx->lock = &dev->stateless_dec.lock;
	} else {
		ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->stateful_dec.m2m_dev,
						    ctx, &queue_init);
		ctx->lock = &dev->stateful_dec.lock;
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