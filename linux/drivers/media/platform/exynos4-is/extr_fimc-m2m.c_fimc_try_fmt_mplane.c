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
typedef  int u32 ;
struct v4l2_pix_format_mplane {scalar_t__ field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {scalar_t__ type; TYPE_2__ fmt; } ;
struct fimc_variant {int min_inp_pixsize; int min_out_pixsize; int min_vsize_align; TYPE_1__* pix_limit; } ;
struct fimc_fmt {int /*<<< orphan*/  color; } ;
struct fimc_dev {struct fimc_variant* variant; } ;
struct fimc_ctx {struct fimc_dev* fimc_dev; } ;
struct TYPE_3__ {int scaler_dis_w; int out_rot_dis_w; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_M2M (scalar_t__) ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 scalar_t__ V4L2_FIELD_ANY ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 scalar_t__ WARN (int /*<<< orphan*/ ,char*) ; 
 int ffs (int) ; 
 int /*<<< orphan*/  fimc_adjust_mplane_format (struct fimc_fmt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_pix_format_mplane*) ; 
 struct fimc_fmt* fimc_find_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fimc_fmt_is_rgb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_m2m_fmt_flags (scalar_t__) ; 
 scalar_t__ tiled_fmt (struct fimc_fmt*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fimc_try_fmt_mplane(struct fimc_ctx *ctx, struct v4l2_format *f)
{
	struct fimc_dev *fimc = ctx->fimc_dev;
	const struct fimc_variant *variant = fimc->variant;
	struct v4l2_pix_format_mplane *pix = &f->fmt.pix_mp;
	struct fimc_fmt *fmt;
	u32 max_w, mod_x, mod_y;

	if (!IS_M2M(f->type))
		return -EINVAL;

	fmt = fimc_find_format(&pix->pixelformat, NULL,
			       get_m2m_fmt_flags(f->type), 0);
	if (WARN(fmt == NULL, "Pixel format lookup failed"))
		return -EINVAL;

	if (pix->field == V4L2_FIELD_ANY)
		pix->field = V4L2_FIELD_NONE;
	else if (pix->field != V4L2_FIELD_NONE)
		return -EINVAL;

	if (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		max_w = variant->pix_limit->scaler_dis_w;
		mod_x = ffs(variant->min_inp_pixsize) - 1;
	} else {
		max_w = variant->pix_limit->out_rot_dis_w;
		mod_x = ffs(variant->min_out_pixsize) - 1;
	}

	if (tiled_fmt(fmt)) {
		mod_x = 6; /* 64 x 32 pixels tile */
		mod_y = 5;
	} else {
		if (variant->min_vsize_align == 1)
			mod_y = fimc_fmt_is_rgb(fmt->color) ? 0 : 1;
		else
			mod_y = ffs(variant->min_vsize_align) - 1;
	}

	v4l_bound_align_image(&pix->width, 16, max_w, mod_x,
		&pix->height, 8, variant->pix_limit->scaler_dis_w, mod_y, 0);

	fimc_adjust_mplane_format(fmt, pix->width, pix->height, &f->fmt.pix_mp);
	return 0;
}