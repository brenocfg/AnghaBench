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
struct v4l2_mbus_framefmt {scalar_t__ code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; } ;
struct v4l2_subdev_format {scalar_t__ which; scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MEDIA_BUS_FMT_FIXED ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int saa711x_set_size (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int saa711x_set_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *fmt = &format->format;

	if (format->pad || fmt->code != MEDIA_BUS_FMT_FIXED)
		return -EINVAL;
	fmt->field = V4L2_FIELD_INTERLACED;
	fmt->colorspace = V4L2_COLORSPACE_SMPTE170M;
	if (format->which == V4L2_SUBDEV_FORMAT_TRY)
		return 0;
	return saa711x_set_size(sd, fmt->width, fmt->height);
}