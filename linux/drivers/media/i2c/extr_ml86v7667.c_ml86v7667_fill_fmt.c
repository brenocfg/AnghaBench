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
struct ml86v7667_priv {int std; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_YUYV8_2X8 ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED_TB ; 
 int V4L2_STD_525_60 ; 
 struct ml86v7667_priv* to_ml86v7667 (struct v4l2_subdev*) ; 

__attribute__((used)) static int ml86v7667_fill_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct ml86v7667_priv *priv = to_ml86v7667(sd);
	struct v4l2_mbus_framefmt *fmt = &format->format;

	if (format->pad)
		return -EINVAL;

	fmt->code = MEDIA_BUS_FMT_YUYV8_2X8;
	fmt->colorspace = V4L2_COLORSPACE_SMPTE170M;
	/* The top field is always transferred first by the chip */
	fmt->field = V4L2_FIELD_INTERLACED_TB;
	fmt->width = 720;
	fmt->height = priv->std & V4L2_STD_525_60 ? 480 : 576;

	return 0;
}