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
struct vicodec_q_data {int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  width; int /*<<< orphan*/  fourcc; int /*<<< orphan*/  height; } ;
struct TYPE_4__ {int /*<<< orphan*/  m2m_ctx; } ;
struct vicodec_ctx {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; TYPE_1__ fh; } ;
struct vb2_queue {int dummy; } ;
struct v4l2_pix_format_mplane {int num_planes; TYPE_3__* plane_fmt; int /*<<< orphan*/  reserved; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; void* field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_pix_format {int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  pixelformat; void* field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_5__ {struct v4l2_pix_format_mplane pix_mp; struct v4l2_pix_format pix; } ;
struct v4l2_format {int type; TYPE_2__ fmt; } ;
struct TYPE_6__ {int /*<<< orphan*/  reserved; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 131 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE 130 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT 129 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE 128 
 void* V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_FWHT ; 
 struct vicodec_q_data* get_q_data (struct vicodec_ctx*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  multiplanar ; 
 struct vb2_queue* v4l2_m2m_get_vq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_g_fmt(struct vicodec_ctx *ctx, struct v4l2_format *f)
{
	struct vb2_queue *vq;
	struct vicodec_q_data *q_data;
	struct v4l2_pix_format_mplane *pix_mp;
	struct v4l2_pix_format *pix;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (!vq)
		return -EINVAL;

	q_data = get_q_data(ctx, f->type);

	switch (f->type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
	case V4L2_BUF_TYPE_VIDEO_OUTPUT:
		if (multiplanar)
			return -EINVAL;
		pix = &f->fmt.pix;
		pix->width = q_data->width;
		pix->height = q_data->height;
		pix->field = V4L2_FIELD_NONE;
		pix->pixelformat = q_data->fourcc;
		if (q_data->fourcc == V4L2_PIX_FMT_FWHT)
			pix->bytesperline = 0;
		else
			pix->bytesperline = q_data->width;
		pix->sizeimage = q_data->sizeimage;
		pix->colorspace = ctx->colorspace;
		pix->xfer_func = ctx->xfer_func;
		pix->ycbcr_enc = ctx->ycbcr_enc;
		pix->quantization = ctx->quantization;
		break;

	case V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
	case V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		if (!multiplanar)
			return -EINVAL;
		pix_mp = &f->fmt.pix_mp;
		pix_mp->width = q_data->width;
		pix_mp->height = q_data->height;
		pix_mp->field = V4L2_FIELD_NONE;
		pix_mp->pixelformat = q_data->fourcc;
		pix_mp->num_planes = 1;
		if (q_data->fourcc == V4L2_PIX_FMT_FWHT)
			pix_mp->plane_fmt[0].bytesperline = 0;
		else
			pix_mp->plane_fmt[0].bytesperline = q_data->width;
		pix_mp->plane_fmt[0].sizeimage = q_data->sizeimage;
		pix_mp->colorspace = ctx->colorspace;
		pix_mp->xfer_func = ctx->xfer_func;
		pix_mp->ycbcr_enc = ctx->ycbcr_enc;
		pix_mp->quantization = ctx->quantization;
		memset(pix_mp->reserved, 0, sizeof(pix_mp->reserved));
		memset(pix_mp->plane_fmt[0].reserved, 0,
		       sizeof(pix_mp->plane_fmt[0].reserved));
		break;
	default:
		return -EINVAL;
	}
	return 0;
}