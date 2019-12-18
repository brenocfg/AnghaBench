#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_pix_format_mplane {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct hantro_fmt {int /*<<< orphan*/  fourcc; } ;
struct hantro_ctx {struct v4l2_pix_format_mplane src_fmt; struct v4l2_pix_format_mplane dst_fmt; struct hantro_fmt const* vpu_dst_fmt; struct hantro_fmt const* vpu_src_fmt; } ;

/* Variables and functions */
 struct hantro_fmt* hantro_get_default_fmt (struct hantro_fmt const*,unsigned int,int) ; 
 struct hantro_fmt* hantro_get_formats (struct hantro_ctx*,unsigned int*) ; 
 scalar_t__ hantro_is_encoder_ctx (struct hantro_ctx*) ; 
 int /*<<< orphan*/  hantro_reset_fmt (struct v4l2_pix_format_mplane*,struct hantro_fmt const*) ; 
 int /*<<< orphan*/  v4l2_fill_pixfmt_mp (struct v4l2_pix_format_mplane*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hantro_reset_raw_fmt(struct hantro_ctx *ctx)
{
	const struct hantro_fmt *raw_vpu_fmt, *formats;
	struct v4l2_pix_format_mplane *raw_fmt, *encoded_fmt;
	unsigned int num_fmts;

	formats = hantro_get_formats(ctx, &num_fmts);
	raw_vpu_fmt = hantro_get_default_fmt(formats, num_fmts, false);

	if (hantro_is_encoder_ctx(ctx)) {
		ctx->vpu_src_fmt = raw_vpu_fmt;
		raw_fmt = &ctx->src_fmt;
		encoded_fmt = &ctx->dst_fmt;
	} else {
		ctx->vpu_dst_fmt = raw_vpu_fmt;
		raw_fmt = &ctx->dst_fmt;
		encoded_fmt = &ctx->src_fmt;
	}

	hantro_reset_fmt(raw_fmt, raw_vpu_fmt);
	v4l2_fill_pixfmt_mp(raw_fmt, raw_vpu_fmt->fourcc,
			    encoded_fmt->width,
			    encoded_fmt->height);
}