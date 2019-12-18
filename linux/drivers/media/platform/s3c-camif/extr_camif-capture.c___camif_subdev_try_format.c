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
struct vp_pix_limits {int /*<<< orphan*/  out_width_align; } ;
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct s3c_camif_variant {struct vp_pix_limits* vp_pix_limits; } ;
struct camif_dev {int /*<<< orphan*/  subdev; struct v4l2_rect camif_crop; struct s3c_camif_variant* variant; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  CAMIF_MAX_PIX_HEIGHT ; 
 int /*<<< orphan*/  CAMIF_MAX_PIX_WIDTH ; 
 int CAMIF_SD_PAD_SINK ; 
 size_t VP_CODEC ; 
 scalar_t__* camif_mbus_formats ; 
 int /*<<< orphan*/  debug ; 
 scalar_t__ ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __camif_subdev_try_format(struct camif_dev *camif,
				struct v4l2_mbus_framefmt *mf, int pad)
{
	const struct s3c_camif_variant *variant = camif->variant;
	const struct vp_pix_limits *pix_lim;
	unsigned int i;

	/* FIXME: constraints against codec or preview path ? */
	pix_lim = &variant->vp_pix_limits[VP_CODEC];

	for (i = 0; i < ARRAY_SIZE(camif_mbus_formats); i++)
		if (camif_mbus_formats[i] == mf->code)
			break;

	if (i == ARRAY_SIZE(camif_mbus_formats))
		mf->code = camif_mbus_formats[0];

	if (pad == CAMIF_SD_PAD_SINK) {
		v4l_bound_align_image(&mf->width, 8, CAMIF_MAX_PIX_WIDTH,
				      ffs(pix_lim->out_width_align) - 1,
				      &mf->height, 8, CAMIF_MAX_PIX_HEIGHT, 0,
				      0);
	} else {
		struct v4l2_rect *crop = &camif->camif_crop;
		v4l_bound_align_image(&mf->width, 8, crop->width,
				      ffs(pix_lim->out_width_align) - 1,
				      &mf->height, 8, crop->height,
				      0, 0);
	}

	v4l2_dbg(1, debug, &camif->subdev, "%ux%u\n", mf->width, mf->height);
}