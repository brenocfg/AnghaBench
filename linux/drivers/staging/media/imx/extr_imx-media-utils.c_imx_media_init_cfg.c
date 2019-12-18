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
struct v4l2_mbus_framefmt {int dummy; } ;
struct v4l2_subdev_format {unsigned int pad; struct v4l2_mbus_framefmt format; int /*<<< orphan*/  which; } ;
struct TYPE_2__ {unsigned int num_pads; } ;
struct v4l2_subdev {TYPE_1__ entity; } ;
typedef  int /*<<< orphan*/  format ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  get_fmt ; 
 int /*<<< orphan*/  memset (struct v4l2_subdev_format*,int /*<<< orphan*/ ,int) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,unsigned int) ; 

int imx_media_init_cfg(struct v4l2_subdev *sd,
		       struct v4l2_subdev_pad_config *cfg)
{
	struct v4l2_mbus_framefmt *mf_try;
	struct v4l2_subdev_format format;
	unsigned int pad;
	int ret;

	for (pad = 0; pad < sd->entity.num_pads; pad++) {
		memset(&format, 0, sizeof(format));

		format.pad = pad;
		format.which = V4L2_SUBDEV_FORMAT_ACTIVE;
		ret = v4l2_subdev_call(sd, pad, get_fmt, NULL, &format);
		if (ret)
			continue;

		mf_try = v4l2_subdev_get_try_format(sd, cfg, pad);
		*mf_try = format.format;
	}

	return 0;
}