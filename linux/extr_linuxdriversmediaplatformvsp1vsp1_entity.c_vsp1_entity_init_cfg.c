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
struct v4l2_subdev_format {unsigned int pad; int /*<<< orphan*/  which; } ;
struct TYPE_2__ {int num_pads; } ;
struct v4l2_subdev {TYPE_1__ entity; } ;
typedef  int /*<<< orphan*/  format ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  memset (struct v4l2_subdev_format*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_fmt ; 
 int /*<<< orphan*/  v4l2_subdev_call (struct v4l2_subdev*,unsigned int,int /*<<< orphan*/ ,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*) ; 

int vsp1_entity_init_cfg(struct v4l2_subdev *subdev,
			 struct v4l2_subdev_pad_config *cfg)
{
	struct v4l2_subdev_format format;
	unsigned int pad;

	for (pad = 0; pad < subdev->entity.num_pads - 1; ++pad) {
		memset(&format, 0, sizeof(format));

		format.pad = pad;
		format.which = cfg ? V4L2_SUBDEV_FORMAT_TRY
			     : V4L2_SUBDEV_FORMAT_ACTIVE;

		v4l2_subdev_call(subdev, pad, set_fmt, cfg, &format);
	}

	return 0;
}