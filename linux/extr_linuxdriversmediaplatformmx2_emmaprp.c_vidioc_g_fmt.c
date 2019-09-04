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
struct TYPE_5__ {int width; int bytesperline; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  field; int /*<<< orphan*/  height; } ;
struct TYPE_6__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; int /*<<< orphan*/  type; } ;
struct emmaprp_q_data {int width; int /*<<< orphan*/  sizeimage; TYPE_1__* fmt; int /*<<< orphan*/  height; } ;
struct emmaprp_ctx {int /*<<< orphan*/  m2m_ctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_YUV420 ; 
 struct emmaprp_q_data* get_q_data (struct emmaprp_ctx*,int /*<<< orphan*/ ) ; 
 struct vb2_queue* v4l2_m2m_get_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_g_fmt(struct emmaprp_ctx *ctx, struct v4l2_format *f)
{
	struct vb2_queue *vq;
	struct emmaprp_q_data *q_data;

	vq = v4l2_m2m_get_vq(ctx->m2m_ctx, f->type);
	if (!vq)
		return -EINVAL;

	q_data = get_q_data(ctx, f->type);

	f->fmt.pix.width	= q_data->width;
	f->fmt.pix.height	= q_data->height;
	f->fmt.pix.field	= V4L2_FIELD_NONE;
	f->fmt.pix.pixelformat	= q_data->fmt->fourcc;
	if (f->fmt.pix.pixelformat == V4L2_PIX_FMT_YUV420)
		f->fmt.pix.bytesperline = q_data->width * 3 / 2;
	else /* YUYV */
		f->fmt.pix.bytesperline = q_data->width * 2;
	f->fmt.pix.sizeimage	= q_data->sizeimage;

	return 0;
}