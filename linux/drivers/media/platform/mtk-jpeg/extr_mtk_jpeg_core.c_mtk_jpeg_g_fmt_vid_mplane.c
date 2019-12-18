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
struct vb2_queue {int dummy; } ;
struct v4l2_plane_pix_format {int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  reserved; } ;
struct v4l2_pix_format_mplane {int pixelformat; int num_planes; struct v4l2_plane_pix_format* plane_fmt; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  quantization; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  reserved; } ;
struct TYPE_4__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {int /*<<< orphan*/  type; TYPE_1__ fmt; } ;
struct mtk_jpeg_q_data {int /*<<< orphan*/ * sizeimage; int /*<<< orphan*/ * bytesperline; TYPE_3__* fmt; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct mtk_jpeg_dev {int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  m2m_ctx; } ;
struct mtk_jpeg_ctx {int /*<<< orphan*/  quantization; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  colorspace; TYPE_2__ fh; struct mtk_jpeg_dev* jpeg; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int fourcc; int colplanes; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mtk_jpeg_ctx* mtk_jpeg_fh_to_ctx (void*) ; 
 struct mtk_jpeg_q_data* mtk_jpeg_get_q_data (struct mtk_jpeg_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,int,int,...) ; 
 struct vb2_queue* v4l2_m2m_get_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_jpeg_g_fmt_vid_mplane(struct file *file, void *priv,
				     struct v4l2_format *f)
{
	struct vb2_queue *vq;
	struct mtk_jpeg_q_data *q_data = NULL;
	struct v4l2_pix_format_mplane *pix_mp = &f->fmt.pix_mp;
	struct mtk_jpeg_ctx *ctx = mtk_jpeg_fh_to_ctx(priv);
	struct mtk_jpeg_dev *jpeg = ctx->jpeg;
	int i;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (!vq)
		return -EINVAL;

	q_data = mtk_jpeg_get_q_data(ctx, f->type);

	memset(pix_mp->reserved, 0, sizeof(pix_mp->reserved));
	pix_mp->width = q_data->w;
	pix_mp->height = q_data->h;
	pix_mp->field = V4L2_FIELD_NONE;
	pix_mp->pixelformat = q_data->fmt->fourcc;
	pix_mp->num_planes = q_data->fmt->colplanes;
	pix_mp->colorspace = ctx->colorspace;
	pix_mp->ycbcr_enc = ctx->ycbcr_enc;
	pix_mp->xfer_func = ctx->xfer_func;
	pix_mp->quantization = ctx->quantization;

	v4l2_dbg(1, debug, &jpeg->v4l2_dev, "(%d) g_fmt:%c%c%c%c wxh:%ux%u\n",
		 f->type,
		 (pix_mp->pixelformat & 0xff),
		 (pix_mp->pixelformat >>  8 & 0xff),
		 (pix_mp->pixelformat >> 16 & 0xff),
		 (pix_mp->pixelformat >> 24 & 0xff),
		 pix_mp->width, pix_mp->height);

	for (i = 0; i < pix_mp->num_planes; i++) {
		struct v4l2_plane_pix_format *pfmt = &pix_mp->plane_fmt[i];

		pfmt->bytesperline = q_data->bytesperline[i];
		pfmt->sizeimage = q_data->sizeimage[i];
		memset(pfmt->reserved, 0, sizeof(pfmt->reserved));

		v4l2_dbg(1, debug, &jpeg->v4l2_dev,
			 "plane[%d] bpl=%u, size=%u\n",
			 i,
			 pfmt->bytesperline,
			 pfmt->sizeimage);
	}
	return 0;
}