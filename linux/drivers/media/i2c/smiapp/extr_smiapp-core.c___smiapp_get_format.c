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
struct TYPE_2__ {int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {scalar_t__ which; size_t pad; TYPE_1__ format; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct smiapp_subdev {size_t source_pad; struct v4l2_rect sink_fmt; struct v4l2_rect* crop; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  __smiapp_get_mbus_code (struct v4l2_subdev*,size_t) ; 
 struct smiapp_subdev* to_smiapp_subdev (struct v4l2_subdev*) ; 
 TYPE_1__* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,size_t) ; 

__attribute__((used)) static int __smiapp_get_format(struct v4l2_subdev *subdev,
			       struct v4l2_subdev_pad_config *cfg,
			       struct v4l2_subdev_format *fmt)
{
	struct smiapp_subdev *ssd = to_smiapp_subdev(subdev);

	if (fmt->which == V4L2_SUBDEV_FORMAT_TRY) {
		fmt->format = *v4l2_subdev_get_try_format(subdev, cfg,
							  fmt->pad);
	} else {
		struct v4l2_rect *r;

		if (fmt->pad == ssd->source_pad)
			r = &ssd->crop[ssd->source_pad];
		else
			r = &ssd->sink_fmt;

		fmt->format.code = __smiapp_get_mbus_code(subdev, fmt->pad);
		fmt->format.width = r->width;
		fmt->format.height = r->height;
		fmt->format.field = V4L2_FIELD_NONE;
	}

	return 0;
}