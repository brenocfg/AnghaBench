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
struct TYPE_7__ {int height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;
struct vpe_q_data {int height; scalar_t__ field; int nplanes; int flags; int /*<<< orphan*/ * bytesperline; TYPE_4__* fmt; int /*<<< orphan*/  width; TYPE_3__ c_rect; int /*<<< orphan*/ * sizeimage; int /*<<< orphan*/  colorspace; } ;
struct TYPE_6__ {int /*<<< orphan*/  m2m_ctx; } ;
struct vpe_ctx {int /*<<< orphan*/  dev; TYPE_2__ fh; } ;
struct vb2_queue {int dummy; } ;
struct v4l2_plane_pix_format {int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; } ;
struct v4l2_pix_format_mplane {int height; scalar_t__ field; int num_planes; struct v4l2_plane_pix_format* plane_fmt; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  width; } ;
struct TYPE_5__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {int /*<<< orphan*/  type; TYPE_1__ fmt; } ;
struct TYPE_8__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int Q_DATA_INTERLACED_ALTERNATE ; 
 int Q_DATA_INTERLACED_SEQ_TB ; 
 int Q_IS_INTERLACED ; 
 scalar_t__ V4L2_FIELD_ALTERNATE ; 
 scalar_t__ V4L2_FIELD_SEQ_TB ; 
 size_t VPE_CHROMA ; 
 size_t VPE_LUMA ; 
 TYPE_4__* find_format (struct v4l2_format*) ; 
 struct vpe_q_data* get_q_data (struct vpe_ctx*,int /*<<< orphan*/ ) ; 
 struct vb2_queue* v4l2_m2m_get_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_busy (struct vb2_queue*) ; 
 int /*<<< orphan*/  vpe_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  vpe_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int __vpe_s_fmt(struct vpe_ctx *ctx, struct v4l2_format *f)
{
	struct v4l2_pix_format_mplane *pix = &f->fmt.pix_mp;
	struct v4l2_plane_pix_format *plane_fmt;
	struct vpe_q_data *q_data;
	struct vb2_queue *vq;
	int i;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (!vq)
		return -EINVAL;

	if (vb2_is_busy(vq)) {
		vpe_err(ctx->dev, "queue busy\n");
		return -EBUSY;
	}

	q_data = get_q_data(ctx, f->type);
	if (!q_data)
		return -EINVAL;

	q_data->fmt		= find_format(f);
	q_data->width		= pix->width;
	q_data->height		= pix->height;
	q_data->colorspace	= pix->colorspace;
	q_data->field		= pix->field;
	q_data->nplanes		= pix->num_planes;

	for (i = 0; i < pix->num_planes; i++) {
		plane_fmt = &pix->plane_fmt[i];

		q_data->bytesperline[i]	= plane_fmt->bytesperline;
		q_data->sizeimage[i]	= plane_fmt->sizeimage;
	}

	q_data->c_rect.left	= 0;
	q_data->c_rect.top	= 0;
	q_data->c_rect.width	= q_data->width;
	q_data->c_rect.height	= q_data->height;

	if (q_data->field == V4L2_FIELD_ALTERNATE)
		q_data->flags |= Q_DATA_INTERLACED_ALTERNATE;
	else if (q_data->field == V4L2_FIELD_SEQ_TB)
		q_data->flags |= Q_DATA_INTERLACED_SEQ_TB;
	else
		q_data->flags &= ~Q_IS_INTERLACED;

	/* the crop height is halved for the case of SEQ_TB buffers */
	if (q_data->flags & Q_DATA_INTERLACED_SEQ_TB)
		q_data->c_rect.height /= 2;

	vpe_dbg(ctx->dev, "Setting format for type %d, wxh: %dx%d, fmt: %d bpl_y %d",
		f->type, q_data->width, q_data->height, q_data->fmt->fourcc,
		q_data->bytesperline[VPE_LUMA]);
	if (q_data->nplanes == 2)
		vpe_dbg(ctx->dev, " bpl_uv %d\n",
			q_data->bytesperline[VPE_CHROMA]);

	return 0;
}