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
struct v4l2_subdev_pad_config {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {scalar_t__ which; TYPE_1__ format; scalar_t__ pad; } ;
struct v4l2_subdev {int dummy; } ;
struct tvp514x_decoder {size_t current_std; TYPE_1__ format; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_UYVY8_2X8 ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_ACTIVE ; 
 struct tvp514x_decoder* to_decoder (struct v4l2_subdev*) ; 
 TYPE_2__* tvp514x_std_list ; 

__attribute__((used)) static int tvp514x_get_pad_format(struct v4l2_subdev *sd,
				  struct v4l2_subdev_pad_config *cfg,
				  struct v4l2_subdev_format *format)
{
	struct tvp514x_decoder *decoder = to_decoder(sd);
	__u32 which = format->which;

	if (format->pad)
		return -EINVAL;

	if (which == V4L2_SUBDEV_FORMAT_ACTIVE) {
		format->format = decoder->format;
		return 0;
	}

	format->format.code = MEDIA_BUS_FMT_UYVY8_2X8;
	format->format.width = tvp514x_std_list[decoder->current_std].width;
	format->format.height = tvp514x_std_list[decoder->current_std].height;
	format->format.colorspace = V4L2_COLORSPACE_SMPTE170M;
	format->format.field = V4L2_FIELD_INTERLACED;

	return 0;
}