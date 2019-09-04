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
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_pix_format {void* height; void* width; } ;
struct v4l2_mbus_framefmt {void* height; void* width; } ;
struct soc_camera_device {struct device* parent; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_geo (struct device*,char*,unsigned int,unsigned int,...) ; 
 unsigned int soc_camera_calc_scale (int /*<<< orphan*/ ,unsigned int,void*) ; 
 void* soc_camera_shift_scale (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

void soc_camera_calc_client_output(struct soc_camera_device *icd,
		struct v4l2_rect *rect, struct v4l2_rect *subrect,
		const struct v4l2_pix_format *pix, struct v4l2_mbus_framefmt *mf,
		unsigned int shift)
{
	struct device *dev = icd->parent;
	unsigned int scale_v, scale_h;

	if (subrect->width == rect->width &&
	    subrect->height == rect->height) {
		/* No sub-cropping */
		mf->width	= pix->width;
		mf->height	= pix->height;
		return;
	}

	/* 1.-2. Current camera scales and subwin - cached. */

	dev_geo(dev, "2: subwin %ux%u@%u:%u\n",
		subrect->width, subrect->height,
		subrect->left, subrect->top);

	/*
	 * 3. Calculate new combined scales from input sub-window to requested
	 *    user window.
	 */

	/*
	 * TODO: CEU cannot scale images larger than VGA to smaller than SubQCIF
	 * (128x96) or larger than VGA. This and similar limitations have to be
	 * taken into account here.
	 */
	scale_h = soc_camera_calc_scale(subrect->width, shift, pix->width);
	scale_v = soc_camera_calc_scale(subrect->height, shift, pix->height);

	dev_geo(dev, "3: scales %u:%u\n", scale_h, scale_v);

	/*
	 * 4. Calculate desired client output window by applying combined scales
	 *    to client (real) input window.
	 */
	mf->width = soc_camera_shift_scale(rect->width, shift, scale_h);
	mf->height = soc_camera_shift_scale(rect->height, shift, scale_v);
}