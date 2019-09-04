#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct vb2_queue {int dummy; } ;
struct v4l2_pix_format {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_6__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {int /*<<< orphan*/  type; TYPE_2__ fmt; } ;
struct file {int dummy; } ;
struct TYPE_8__ {scalar_t__ top; scalar_t__ left; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct bdisp_frame {TYPE_4__ crop; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  fmt; } ;
struct TYPE_5__ {int /*<<< orphan*/  m2m_ctx; } ;
struct bdisp_ctx {TYPE_3__* bdisp_dev; struct bdisp_frame dst; struct bdisp_frame src; TYPE_1__ fh; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDISP_DST_FMT ; 
 int /*<<< orphan*/  BDISP_PARAMS ; 
 int /*<<< orphan*/  BDISP_SRC_FMT ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  bdisp_ctx_state_lock_set (int /*<<< orphan*/ ,struct bdisp_ctx*) ; 
 int /*<<< orphan*/  bdisp_find_fmt (int /*<<< orphan*/ ) ; 
 int bdisp_try_fmt (struct file*,void*,struct v4l2_format*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct bdisp_ctx* fh_to_ctx (void*) ; 
 struct vb2_queue* v4l2_m2m_get_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_streaming (struct vb2_queue*) ; 

__attribute__((used)) static int bdisp_s_fmt(struct file *file, void *fh, struct v4l2_format *f)
{
	struct bdisp_ctx *ctx = fh_to_ctx(fh);
	struct vb2_queue *vq;
	struct bdisp_frame *frame;
	struct v4l2_pix_format *pix;
	int ret;
	u32 state;

	ret = bdisp_try_fmt(file, fh, f);
	if (ret) {
		dev_err(ctx->bdisp_dev->dev, "Cannot set format\n");
		return ret;
	}

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (vb2_is_streaming(vq)) {
		dev_err(ctx->bdisp_dev->dev, "queue (%d) busy\n", f->type);
		return -EBUSY;
	}

	frame = (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) ?
			&ctx->src : &ctx->dst;
	pix = &f->fmt.pix;
	frame->fmt = bdisp_find_fmt(pix->pixelformat);
	if (!frame->fmt) {
		dev_err(ctx->bdisp_dev->dev, "Unknown format 0x%x\n",
			pix->pixelformat);
		return -EINVAL;
	}

	frame->width = pix->width;
	frame->height = pix->height;
	frame->bytesperline = pix->bytesperline;
	frame->sizeimage = pix->sizeimage;
	frame->field = pix->field;
	if (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		frame->colorspace = pix->colorspace;

	frame->crop.width = frame->width;
	frame->crop.height = frame->height;
	frame->crop.left = 0;
	frame->crop.top = 0;

	state = BDISP_PARAMS;
	state |= (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) ?
			BDISP_DST_FMT : BDISP_SRC_FMT;
	bdisp_ctx_state_lock_set(state, ctx);

	return 0;
}