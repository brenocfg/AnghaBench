#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int code; int field; int height; scalar_t__ width; } ;
struct v4l2_subdev_format {TYPE_2__ format; int /*<<< orphan*/  pad; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_3__ {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  field; } ;
struct rvin_dev {int mbus_code; TYPE_1__ format; } ;
struct media_pad {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int EPIPE ; 
#define  MEDIA_BUS_FMT_RGB888_1X24 141 
#define  MEDIA_BUS_FMT_UYVY10_2X10 140 
#define  MEDIA_BUS_FMT_UYVY8_1X16 139 
#define  MEDIA_BUS_FMT_UYVY8_2X8 138 
#define  MEDIA_BUS_FMT_YUYV8_1X16 137 
#define  V4L2_FIELD_ALTERNATE 136 
#define  V4L2_FIELD_BOTTOM 135 
#define  V4L2_FIELD_INTERLACED 134 
#define  V4L2_FIELD_INTERLACED_BT 133 
#define  V4L2_FIELD_INTERLACED_TB 132 
#define  V4L2_FIELD_NONE 131 
#define  V4L2_FIELD_SEQ_BT 130 
#define  V4L2_FIELD_SEQ_TB 129 
#define  V4L2_FIELD_TOP 128 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  get_fmt ; 
 scalar_t__ v4l2_subdev_call (struct v4l2_subdev*,struct media_pad*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 

__attribute__((used)) static int rvin_mc_validate_format(struct rvin_dev *vin, struct v4l2_subdev *sd,
				   struct media_pad *pad)
{
	struct v4l2_subdev_format fmt = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};

	fmt.pad = pad->index;
	if (v4l2_subdev_call(sd, pad, get_fmt, NULL, &fmt))
		return -EPIPE;

	switch (fmt.format.code) {
	case MEDIA_BUS_FMT_YUYV8_1X16:
	case MEDIA_BUS_FMT_UYVY8_1X16:
	case MEDIA_BUS_FMT_UYVY8_2X8:
	case MEDIA_BUS_FMT_UYVY10_2X10:
	case MEDIA_BUS_FMT_RGB888_1X24:
		vin->mbus_code = fmt.format.code;
		break;
	default:
		return -EPIPE;
	}

	switch (fmt.format.field) {
	case V4L2_FIELD_TOP:
	case V4L2_FIELD_BOTTOM:
	case V4L2_FIELD_NONE:
	case V4L2_FIELD_INTERLACED_TB:
	case V4L2_FIELD_INTERLACED_BT:
	case V4L2_FIELD_INTERLACED:
	case V4L2_FIELD_SEQ_TB:
	case V4L2_FIELD_SEQ_BT:
		/* Supported natively */
		break;
	case V4L2_FIELD_ALTERNATE:
		switch (vin->format.field) {
		case V4L2_FIELD_TOP:
		case V4L2_FIELD_BOTTOM:
		case V4L2_FIELD_NONE:
			break;
		case V4L2_FIELD_INTERLACED_TB:
		case V4L2_FIELD_INTERLACED_BT:
		case V4L2_FIELD_INTERLACED:
		case V4L2_FIELD_SEQ_TB:
		case V4L2_FIELD_SEQ_BT:
			/* Use VIN hardware to combine the two fields */
			fmt.format.height *= 2;
			break;
		default:
			return -EPIPE;
		}
		break;
	default:
		return -EPIPE;
	}

	if (fmt.format.width != vin->format.width ||
	    fmt.format.height != vin->format.height ||
	    fmt.format.code != vin->mbus_code)
		return -EPIPE;

	return 0;
}