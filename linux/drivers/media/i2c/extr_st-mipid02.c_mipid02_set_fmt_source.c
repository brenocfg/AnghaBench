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
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {scalar_t__ which; TYPE_1__ format; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct mipid02_dev {TYPE_1__ fmt; } ;

/* Variables and functions */
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  serial_to_parallel_code (int /*<<< orphan*/ ) ; 
 struct mipid02_dev* to_mipid02_dev (struct v4l2_subdev*) ; 
 TYPE_1__* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mipid02_set_fmt_source(struct v4l2_subdev *sd,
				   struct v4l2_subdev_pad_config *cfg,
				   struct v4l2_subdev_format *format)
{
	struct mipid02_dev *bridge = to_mipid02_dev(sd);

	/* source pad mirror active sink pad */
	format->format = bridge->fmt;
	/* but code may need to be converted */
	format->format.code = serial_to_parallel_code(format->format.code);

	/* only apply format for V4L2_SUBDEV_FORMAT_TRY case */
	if (format->which != V4L2_SUBDEV_FORMAT_TRY)
		return;

	*v4l2_subdev_get_try_format(sd, cfg, format->pad) = format->format;
}