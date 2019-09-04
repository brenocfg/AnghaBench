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
typedef  int u8 ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int code; } ;
struct v4l2_subdev_format {scalar_t__ which; scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MEDIA_BUS_FMT_UYVY8_1X16 129 
#define  MEDIA_BUS_FMT_UYVY8_2X8 128 
 scalar_t__ V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int adv7175_read (struct v4l2_subdev*,int) ; 
 int adv7175_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int adv7175_set_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *mf = &format->format;
	u8 val = adv7175_read(sd, 0x7);
	int ret = 0;

	if (format->pad)
		return -EINVAL;

	switch (mf->code) {
	case MEDIA_BUS_FMT_UYVY8_2X8:
		val &= ~0x40;
		break;

	case MEDIA_BUS_FMT_UYVY8_1X16:
		val |= 0x40;
		break;

	default:
		v4l2_dbg(1, debug, sd,
			"illegal v4l2_mbus_framefmt code: %d\n", mf->code);
		return -EINVAL;
	}

	if (format->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		ret = adv7175_write(sd, 0x7, val);

	return ret;
}