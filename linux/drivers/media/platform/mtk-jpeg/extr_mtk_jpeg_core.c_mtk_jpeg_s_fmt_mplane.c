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
struct vb2_queue {int dummy; } ;
struct v4l2_pix_format_mplane {TYPE_3__* plane_fmt; int /*<<< orphan*/  quantization; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_5__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {int /*<<< orphan*/  type; TYPE_1__ fmt; } ;
struct mtk_jpeg_q_data {int /*<<< orphan*/ * sizeimage; int /*<<< orphan*/ * bytesperline; TYPE_4__* fmt; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct mtk_jpeg_dev {int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  m2m_ctx; } ;
struct mtk_jpeg_ctx {int /*<<< orphan*/  quantization; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  colorspace; TYPE_2__ fh; struct mtk_jpeg_dev* jpeg; } ;
struct TYPE_8__ {int fourcc; int colplanes; } ;
struct TYPE_7__ {int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 unsigned int MTK_JPEG_FMT_TYPE_CAPTURE ; 
 unsigned int MTK_JPEG_FMT_TYPE_OUTPUT ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 TYPE_4__* mtk_jpeg_find_format (struct mtk_jpeg_ctx*,int /*<<< orphan*/ ,unsigned int) ; 
 struct mtk_jpeg_q_data* mtk_jpeg_get_q_data (struct mtk_jpeg_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,int,int,...) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 struct vb2_queue* v4l2_m2m_get_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_busy (struct vb2_queue*) ; 

__attribute__((used)) static int mtk_jpeg_s_fmt_mplane(struct mtk_jpeg_ctx *ctx,
				 struct v4l2_format *f)
{
	struct vb2_queue *vq;
	struct mtk_jpeg_q_data *q_data = NULL;
	struct v4l2_pix_format_mplane *pix_mp = &f->fmt.pix_mp;
	struct mtk_jpeg_dev *jpeg = ctx->jpeg;
	unsigned int f_type;
	int i;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (!vq)
		return -EINVAL;

	q_data = mtk_jpeg_get_q_data(ctx, f->type);

	if (vb2_is_busy(vq)) {
		v4l2_err(&jpeg->v4l2_dev, "queue busy\n");
		return -EBUSY;
	}

	f_type = V4L2_TYPE_IS_OUTPUT(f->type) ?
			 MTK_JPEG_FMT_TYPE_OUTPUT : MTK_JPEG_FMT_TYPE_CAPTURE;

	q_data->fmt = mtk_jpeg_find_format(ctx, pix_mp->pixelformat, f_type);
	q_data->w = pix_mp->width;
	q_data->h = pix_mp->height;
	ctx->colorspace = pix_mp->colorspace;
	ctx->ycbcr_enc = pix_mp->ycbcr_enc;
	ctx->xfer_func = pix_mp->xfer_func;
	ctx->quantization = pix_mp->quantization;

	v4l2_dbg(1, debug, &jpeg->v4l2_dev, "(%d) s_fmt:%c%c%c%c wxh:%ux%u\n",
		 f->type,
		 (q_data->fmt->fourcc & 0xff),
		 (q_data->fmt->fourcc >>  8 & 0xff),
		 (q_data->fmt->fourcc >> 16 & 0xff),
		 (q_data->fmt->fourcc >> 24 & 0xff),
		 q_data->w, q_data->h);

	for (i = 0; i < q_data->fmt->colplanes; i++) {
		q_data->bytesperline[i] = pix_mp->plane_fmt[i].bytesperline;
		q_data->sizeimage[i] = pix_mp->plane_fmt[i].sizeimage;

		v4l2_dbg(1, debug, &jpeg->v4l2_dev,
			 "plane[%d] bpl=%u, size=%u\n",
			 i, q_data->bytesperline[i], q_data->sizeimage[i]);
	}

	return 0;
}