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
typedef  void* u32 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {scalar_t__ field; scalar_t__ code; void* height; void* width; int /*<<< orphan*/  colorspace; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MEDIA_BUS_FMT_UYVY8_2X8 ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 scalar_t__ V4L2_FIELD_ANY ; 
 scalar_t__ V4L2_FIELD_INTERLACED_BT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int tw9910_set_frame (struct v4l2_subdev*,void**,void**) ; 

__attribute__((used)) static int tw9910_s_fmt(struct v4l2_subdev *sd,
			struct v4l2_mbus_framefmt *mf)
{
	u32 width = mf->width, height = mf->height;
	int ret;

	WARN_ON(mf->field != V4L2_FIELD_ANY &&
		mf->field != V4L2_FIELD_INTERLACED_BT);

	/* Check color format. */
	if (mf->code != MEDIA_BUS_FMT_UYVY8_2X8)
		return -EINVAL;

	mf->colorspace = V4L2_COLORSPACE_SMPTE170M;

	ret = tw9910_set_frame(sd, &width, &height);
	if (ret)
		return ret;

	mf->width	= width;
	mf->height	= height;

	return 0;
}