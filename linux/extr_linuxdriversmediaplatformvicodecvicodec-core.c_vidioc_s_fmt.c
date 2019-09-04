#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vicodec_q_data {int /*<<< orphan*/  fourcc; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  sizeimage; } ;
struct TYPE_4__ {int /*<<< orphan*/  m2m_ctx; } ;
struct vicodec_ctx {int /*<<< orphan*/  dev; int /*<<< orphan*/  is_enc; TYPE_1__ fh; } ;
struct vb2_queue {int dummy; } ;
struct v4l2_pix_format_mplane {TYPE_3__* plane_fmt; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; } ;
struct v4l2_pix_format {int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_5__ {struct v4l2_pix_format_mplane pix_mp; struct v4l2_pix_format pix; } ;
struct v4l2_format {int type; TYPE_2__ fmt; } ;
struct TYPE_6__ {int /*<<< orphan*/  sizeimage; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 131 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE 130 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT 129 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE 128 
 int /*<<< orphan*/  V4L2_TYPE_IS_OUTPUT (int) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vicodec_q_data* get_q_data (struct vicodec_ctx*,int) ; 
 struct vb2_queue* v4l2_m2m_get_vq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vb2_is_busy (struct vb2_queue*) ; 

__attribute__((used)) static int vidioc_s_fmt(struct vicodec_ctx *ctx, struct v4l2_format *f)
{
	struct vicodec_q_data *q_data;
	struct vb2_queue *vq;
	bool fmt_changed = true;
	struct v4l2_pix_format_mplane *pix_mp;
	struct v4l2_pix_format *pix;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (!vq)
		return -EINVAL;

	q_data = get_q_data(ctx, f->type);
	if (!q_data)
		return -EINVAL;

	switch (f->type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
	case V4L2_BUF_TYPE_VIDEO_OUTPUT:
		pix = &f->fmt.pix;
		if (ctx->is_enc && V4L2_TYPE_IS_OUTPUT(f->type))
			fmt_changed =
				q_data->fourcc != pix->pixelformat ||
				q_data->width != pix->width ||
				q_data->height != pix->height;

		if (vb2_is_busy(vq) && fmt_changed)
			return -EBUSY;

		q_data->fourcc = pix->pixelformat;
		q_data->width = pix->width;
		q_data->height = pix->height;
		q_data->sizeimage = pix->sizeimage;
		break;
	case V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
	case V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		pix_mp = &f->fmt.pix_mp;
		if (ctx->is_enc && V4L2_TYPE_IS_OUTPUT(f->type))
			fmt_changed =
				q_data->fourcc != pix_mp->pixelformat ||
				q_data->width != pix_mp->width ||
				q_data->height != pix_mp->height;

		if (vb2_is_busy(vq) && fmt_changed)
			return -EBUSY;

		q_data->fourcc = pix_mp->pixelformat;
		q_data->width = pix_mp->width;
		q_data->height = pix_mp->height;
		q_data->sizeimage = pix_mp->plane_fmt[0].sizeimage;
		break;
	default:
		return -EINVAL;
	}

	dprintk(ctx->dev,
		"Setting format for type %d, wxh: %dx%d, fourcc: %08x\n",
		f->type, q_data->width, q_data->height, q_data->fourcc);

	return 0;
}