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
struct vpe_q_data {int nplanes; int /*<<< orphan*/ * sizeimage; int /*<<< orphan*/ * bytesperline; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; TYPE_3__* fmt; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_6__ {int /*<<< orphan*/  m2m_ctx; } ;
struct vpe_ctx {TYPE_2__ fh; } ;
struct vb2_queue {int dummy; } ;
struct v4l2_pix_format_mplane {int num_planes; TYPE_4__* plane_fmt; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_5__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {int /*<<< orphan*/  type; TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; } ;
struct TYPE_7__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 struct vpe_ctx* file2ctx (struct file*) ; 
 struct vpe_q_data* get_q_data (struct vpe_ctx*,int /*<<< orphan*/ ) ; 
 struct vb2_queue* v4l2_m2m_get_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpe_g_fmt(struct file *file, void *priv, struct v4l2_format *f)
{
	struct v4l2_pix_format_mplane *pix = &f->fmt.pix_mp;
	struct vpe_ctx *ctx = file2ctx(file);
	struct vb2_queue *vq;
	struct vpe_q_data *q_data;
	int i;

	vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (!vq)
		return -EINVAL;

	q_data = get_q_data(ctx, f->type);

	pix->width = q_data->width;
	pix->height = q_data->height;
	pix->pixelformat = q_data->fmt->fourcc;
	pix->field = q_data->field;

	if (V4L2_TYPE_IS_OUTPUT(f->type)) {
		pix->colorspace = q_data->colorspace;
	} else {
		struct vpe_q_data *s_q_data;

		/* get colorspace from the source queue */
		s_q_data = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);

		pix->colorspace = s_q_data->colorspace;
	}

	pix->num_planes = q_data->nplanes;

	for (i = 0; i < pix->num_planes; i++) {
		pix->plane_fmt[i].bytesperline = q_data->bytesperline[i];
		pix->plane_fmt[i].sizeimage = q_data->sizeimage[i];
	}

	return 0;
}