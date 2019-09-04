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
struct v4l2_mbus_framefmt {unsigned int width; unsigned int height; int /*<<< orphan*/  colorspace; } ;
struct v4l2_subdev_format {struct v4l2_mbus_framefmt format; int /*<<< orphan*/  which; } ;
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct soc_camera_device {struct device* parent; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int client_set_fmt (struct soc_camera_device*,struct v4l2_rect*,struct v4l2_rect*,unsigned int,unsigned int,struct v4l2_subdev_format*,int) ; 
 int /*<<< orphan*/  dev_geo (struct device*,char*,unsigned int,unsigned int) ; 
 unsigned int soc_camera_calc_scale (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 unsigned int soc_camera_shift_scale (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

int soc_camera_client_scale(struct soc_camera_device *icd,
			struct v4l2_rect *rect, struct v4l2_rect *subrect,
			struct v4l2_mbus_framefmt *mf,
			unsigned int *width, unsigned int *height,
			bool host_can_scale, unsigned int shift)
{
	struct device *dev = icd->parent;
	struct v4l2_subdev_format fmt_tmp = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.format = *mf,
	};
	struct v4l2_mbus_framefmt *mf_tmp = &fmt_tmp.format;
	unsigned int scale_h, scale_v;
	int ret;

	/*
	 * 5. Apply iterative camera S_FMT for camera user window (also updates
	 *    client crop cache and the imaginary sub-rectangle).
	 */
	ret = client_set_fmt(icd, rect, subrect, *width, *height,
			   &fmt_tmp, host_can_scale);
	if (ret < 0)
		return ret;

	dev_geo(dev, "5: camera scaled to %ux%u\n",
		mf_tmp->width, mf_tmp->height);

	/* 6. Retrieve camera output window (g_fmt) */

	/* unneeded - it is already in "mf_tmp" */

	/* 7. Calculate new client scales. */
	scale_h = soc_camera_calc_scale(rect->width, shift, mf_tmp->width);
	scale_v = soc_camera_calc_scale(rect->height, shift, mf_tmp->height);

	mf->width	= mf_tmp->width;
	mf->height	= mf_tmp->height;
	mf->colorspace	= mf_tmp->colorspace;

	/*
	 * 8. Calculate new host crop - apply camera scales to previously
	 *    updated "effective" crop.
	 */
	*width = soc_camera_shift_scale(subrect->width, shift, scale_h);
	*height = soc_camera_shift_scale(subrect->height, shift, scale_v);

	dev_geo(dev, "8: new client sub-window %ux%u\n", *width, *height);

	return 0;
}