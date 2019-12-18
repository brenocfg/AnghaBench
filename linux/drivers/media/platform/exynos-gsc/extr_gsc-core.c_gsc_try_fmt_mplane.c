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
typedef  int u32 ;
struct v4l2_plane_pix_format {int bytesperline; int /*<<< orphan*/  sizeimage; } ;
struct v4l2_pix_format_mplane {int width; int height; scalar_t__ field; int num_planes; struct v4l2_plane_pix_format* plane_fmt; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_5__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {int /*<<< orphan*/  type; TYPE_1__ fmt; } ;
struct gsc_variant {TYPE_4__* pix_min; TYPE_3__* pix_align; TYPE_2__* pix_max; } ;
struct gsc_fmt {int num_planes; int num_comp; int* depth; int /*<<< orphan*/  color; } ;
struct gsc_dev {struct gsc_variant* variant; } ;
struct gsc_ctx {int /*<<< orphan*/  out_colorspace; struct gsc_dev* gsc_dev; } ;
struct TYPE_8__ {int org_w; int org_h; int target_rot_dis_w; int target_rot_dis_h; } ;
struct TYPE_7__ {int /*<<< orphan*/  org_h; int /*<<< orphan*/  org_w; } ;
struct TYPE_6__ {int target_rot_dis_w; int target_rot_dis_h; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_FIELD_ANY ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 int ffs (int /*<<< orphan*/ ) ; 
 struct gsc_fmt* find_fmt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_yuv420 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int*,int,int,int,int*,int,int,int,int /*<<< orphan*/ ) ; 

int gsc_try_fmt_mplane(struct gsc_ctx *ctx, struct v4l2_format *f)
{
	struct gsc_dev *gsc = ctx->gsc_dev;
	struct gsc_variant *variant = gsc->variant;
	struct v4l2_pix_format_mplane *pix_mp = &f->fmt.pix_mp;
	const struct gsc_fmt *fmt;
	u32 max_w, max_h, mod_x, mod_y;
	u32 min_w, min_h, tmp_w, tmp_h;
	int i;

	pr_debug("user put w: %d, h: %d", pix_mp->width, pix_mp->height);

	fmt = find_fmt(&pix_mp->pixelformat, NULL, 0);
	if (!fmt) {
		pr_err("pixelformat format (0x%X) invalid\n",
						pix_mp->pixelformat);
		return -EINVAL;
	}

	if (pix_mp->field == V4L2_FIELD_ANY)
		pix_mp->field = V4L2_FIELD_NONE;
	else if (pix_mp->field != V4L2_FIELD_NONE) {
		pr_debug("Not supported field order(%d)\n", pix_mp->field);
		return -EINVAL;
	}

	max_w = variant->pix_max->target_rot_dis_w;
	max_h = variant->pix_max->target_rot_dis_h;

	mod_x = ffs(variant->pix_align->org_w) - 1;
	if (is_yuv420(fmt->color))
		mod_y = ffs(variant->pix_align->org_h) - 1;
	else
		mod_y = ffs(variant->pix_align->org_h) - 2;

	if (V4L2_TYPE_IS_OUTPUT(f->type)) {
		min_w = variant->pix_min->org_w;
		min_h = variant->pix_min->org_h;
	} else {
		min_w = variant->pix_min->target_rot_dis_w;
		min_h = variant->pix_min->target_rot_dis_h;
		pix_mp->colorspace = ctx->out_colorspace;
	}

	pr_debug("mod_x: %d, mod_y: %d, max_w: %d, max_h = %d",
			mod_x, mod_y, max_w, max_h);

	/* To check if image size is modified to adjust parameter against
	   hardware abilities */
	tmp_w = pix_mp->width;
	tmp_h = pix_mp->height;

	v4l_bound_align_image(&pix_mp->width, min_w, max_w, mod_x,
		&pix_mp->height, min_h, max_h, mod_y, 0);
	if (tmp_w != pix_mp->width || tmp_h != pix_mp->height)
		pr_debug("Image size has been modified from %dx%d to %dx%d\n",
			 tmp_w, tmp_h, pix_mp->width, pix_mp->height);

	pix_mp->num_planes = fmt->num_planes;

	if (V4L2_TYPE_IS_OUTPUT(f->type))
		ctx->out_colorspace = pix_mp->colorspace;

	for (i = 0; i < pix_mp->num_planes; ++i) {
		struct v4l2_plane_pix_format *plane_fmt = &pix_mp->plane_fmt[i];
		u32 bpl = plane_fmt->bytesperline;

		if (fmt->num_comp == 1 && /* Packed */
		    (bpl == 0 || (bpl * 8 / fmt->depth[i]) < pix_mp->width))
			bpl = pix_mp->width * fmt->depth[i] / 8;

		if (fmt->num_comp > 1 && /* Planar */
		    (bpl == 0 || bpl < pix_mp->width))
			bpl = pix_mp->width;

		if (i != 0 && fmt->num_comp == 3)
			bpl /= 2;

		plane_fmt->bytesperline = bpl;
		plane_fmt->sizeimage = max(pix_mp->width * pix_mp->height *
					   fmt->depth[i] / 8,
					   plane_fmt->sizeimage);
		pr_debug("[%d]: bpl: %d, sizeimage: %d",
				i, bpl, pix_mp->plane_fmt[i].sizeimage);
	}

	return 0;
}