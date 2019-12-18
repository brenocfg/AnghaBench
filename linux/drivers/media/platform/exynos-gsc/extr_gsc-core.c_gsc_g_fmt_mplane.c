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
struct v4l2_pix_format_mplane {int width; int height; int num_planes; TYPE_3__* plane_fmt; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  field; } ;
struct TYPE_4__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {TYPE_1__ fmt; int /*<<< orphan*/  type; } ;
struct gsc_frame {int f_width; int f_height; TYPE_2__* fmt; } ;
struct gsc_ctx {int /*<<< orphan*/  out_colorspace; } ;
struct TYPE_6__ {int bytesperline; int sizeimage; } ;
struct TYPE_5__ {int num_planes; int* depth; int /*<<< orphan*/  pixelformat; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct gsc_frame*) ; 
 int PTR_ERR (struct gsc_frame*) ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct gsc_frame* ctx_get_frame (struct gsc_ctx*,int /*<<< orphan*/ ) ; 

int gsc_g_fmt_mplane(struct gsc_ctx *ctx, struct v4l2_format *f)
{
	struct gsc_frame *frame;
	struct v4l2_pix_format_mplane *pix_mp;
	int i;

	frame = ctx_get_frame(ctx, f->type);
	if (IS_ERR(frame))
		return PTR_ERR(frame);

	pix_mp = &f->fmt.pix_mp;

	pix_mp->width		= frame->f_width;
	pix_mp->height		= frame->f_height;
	pix_mp->field		= V4L2_FIELD_NONE;
	pix_mp->pixelformat	= frame->fmt->pixelformat;
	pix_mp->num_planes	= frame->fmt->num_planes;
	pix_mp->colorspace = ctx->out_colorspace;

	for (i = 0; i < pix_mp->num_planes; ++i) {
		pix_mp->plane_fmt[i].bytesperline = (frame->f_width *
			frame->fmt->depth[i]) / 8;
		pix_mp->plane_fmt[i].sizeimage =
			 pix_mp->plane_fmt[i].bytesperline * frame->f_height;
	}

	return 0;
}