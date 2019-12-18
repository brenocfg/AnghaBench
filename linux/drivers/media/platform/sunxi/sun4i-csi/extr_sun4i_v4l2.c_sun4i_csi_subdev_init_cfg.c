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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI_SUBDEV_SINK ; 
 struct v4l2_mbus_framefmt sun4i_csi_pad_fmt_default ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun4i_csi_subdev_init_cfg(struct v4l2_subdev *subdev,
				     struct v4l2_subdev_pad_config *cfg)
{
	struct v4l2_mbus_framefmt *fmt;

	fmt = v4l2_subdev_get_try_format(subdev, cfg, CSI_SUBDEV_SINK);
	*fmt = sun4i_csi_pad_fmt_default;

	return 0;
}