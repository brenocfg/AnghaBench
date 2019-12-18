#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_pix_format_mplane {int num_planes; int width; int height; TYPE_2__* plane_fmt; } ;
struct TYPE_3__ {int min_width; int min_height; } ;
struct hantro_fmt {int max_depth; scalar_t__ header_size; TYPE_1__ frmsize; } ;
struct hantro_ctx {struct v4l2_pix_format_mplane src_fmt; struct hantro_fmt const* vpu_src_fmt; struct v4l2_pix_format_mplane dst_fmt; struct hantro_fmt const* vpu_dst_fmt; } ;
struct TYPE_4__ {scalar_t__ sizeimage; } ;

/* Variables and functions */
 struct hantro_fmt* hantro_get_default_fmt (struct hantro_fmt const*,unsigned int,int) ; 
 struct hantro_fmt* hantro_get_formats (struct hantro_ctx*,unsigned int*) ; 
 scalar_t__ hantro_is_encoder_ctx (struct hantro_ctx*) ; 
 int /*<<< orphan*/  hantro_reset_fmt (struct v4l2_pix_format_mplane*,struct hantro_fmt const*) ; 

__attribute__((used)) static void
hantro_reset_encoded_fmt(struct hantro_ctx *ctx)
{
	const struct hantro_fmt *vpu_fmt, *formats;
	struct v4l2_pix_format_mplane *fmt;
	unsigned int num_fmts;

	formats = hantro_get_formats(ctx, &num_fmts);
	vpu_fmt = hantro_get_default_fmt(formats, num_fmts, true);

	if (hantro_is_encoder_ctx(ctx)) {
		ctx->vpu_dst_fmt = vpu_fmt;
		fmt = &ctx->dst_fmt;
	} else {
		ctx->vpu_src_fmt = vpu_fmt;
		fmt = &ctx->src_fmt;
	}

	hantro_reset_fmt(fmt, vpu_fmt);
	fmt->num_planes = 1;
	fmt->width = vpu_fmt->frmsize.min_width;
	fmt->height = vpu_fmt->frmsize.min_height;
	fmt->plane_fmt[0].sizeimage = vpu_fmt->header_size +
				fmt->width * fmt->height * vpu_fmt->max_depth;
}