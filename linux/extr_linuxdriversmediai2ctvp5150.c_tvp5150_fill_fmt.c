#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int height; int /*<<< orphan*/  width; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int height; int /*<<< orphan*/  width; } ;
struct tvp5150 {TYPE_1__ rect; } ;

/* Variables and functions */
 scalar_t__ DEMOD_PAD_VID_OUT ; 
 int EINVAL ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_UYVY8_2X8 ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_ALTERNATE ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  dev_dbg_lvl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct tvp5150* to_tvp5150 (struct v4l2_subdev*) ; 

__attribute__((used)) static int tvp5150_fill_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *f;
	struct tvp5150 *decoder = to_tvp5150(sd);

	if (!format || (format->pad != DEMOD_PAD_VID_OUT))
		return -EINVAL;

	f = &format->format;

	f->width = decoder->rect.width;
	f->height = decoder->rect.height / 2;

	f->code = MEDIA_BUS_FMT_UYVY8_2X8;
	f->field = V4L2_FIELD_ALTERNATE;
	f->colorspace = V4L2_COLORSPACE_SMPTE170M;

	dev_dbg_lvl(sd->dev, 1, debug, "width = %d, height = %d\n", f->width,
			f->height);
	return 0;
}