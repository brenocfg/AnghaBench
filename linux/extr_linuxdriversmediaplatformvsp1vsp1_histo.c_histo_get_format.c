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
struct TYPE_2__ {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; scalar_t__ height; scalar_t__ width; int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {scalar_t__ pad; TYPE_1__ format; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 scalar_t__ HISTO_PAD_SOURCE ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_FIXED ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_RAW ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int vsp1_subdev_get_pad_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*) ; 

__attribute__((used)) static int histo_get_format(struct v4l2_subdev *subdev,
			    struct v4l2_subdev_pad_config *cfg,
			    struct v4l2_subdev_format *fmt)
{
	if (fmt->pad == HISTO_PAD_SOURCE) {
		fmt->format.code = MEDIA_BUS_FMT_FIXED;
		fmt->format.width = 0;
		fmt->format.height = 0;
		fmt->format.field = V4L2_FIELD_NONE;
		fmt->format.colorspace = V4L2_COLORSPACE_RAW;
		return 0;
	}

	return vsp1_subdev_get_pad_format(subdev, cfg, fmt);
}