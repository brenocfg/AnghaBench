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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int width; int height; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_SBGGR8_1X8 ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  memset (struct v4l2_mbus_framefmt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ov5647_set_get_fmt(struct v4l2_subdev *sd,
			      struct v4l2_subdev_pad_config *cfg,
			      struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *fmt = &format->format;

	if (format->pad != 0)
		return -EINVAL;

	/* Only one format is supported, so return that */
	memset(fmt, 0, sizeof(*fmt));
	fmt->code = MEDIA_BUS_FMT_SBGGR8_1X8;
	fmt->colorspace = V4L2_COLORSPACE_SRGB;
	fmt->field = V4L2_FIELD_NONE;
	fmt->width = 640;
	fmt->height = 480;

	return 0;
}