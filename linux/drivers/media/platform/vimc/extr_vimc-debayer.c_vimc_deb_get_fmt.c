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
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct vimc_deb_device {int /*<<< orphan*/  src_code; TYPE_1__ sink_fmt; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_format {scalar_t__ which; TYPE_1__ format; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_SRC (int /*<<< orphan*/ ) ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 struct vimc_deb_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 TYPE_1__* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vimc_deb_get_fmt(struct v4l2_subdev *sd,
			    struct v4l2_subdev_pad_config *cfg,
			    struct v4l2_subdev_format *fmt)
{
	struct vimc_deb_device *vdeb = v4l2_get_subdevdata(sd);

	/* Get the current sink format */
	fmt->format = fmt->which == V4L2_SUBDEV_FORMAT_TRY ?
		      *v4l2_subdev_get_try_format(sd, cfg, 0) :
		      vdeb->sink_fmt;

	/* Set the right code for the source pad */
	if (IS_SRC(fmt->pad))
		fmt->format.code = vdeb->src_code;

	return 0;
}