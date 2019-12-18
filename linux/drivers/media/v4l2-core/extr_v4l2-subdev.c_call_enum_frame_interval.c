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
struct v4l2_subdev_frame_interval_enum {int /*<<< orphan*/  which; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {TYPE_2__* ops; } ;
struct TYPE_4__ {TYPE_1__* pad; } ;
struct TYPE_3__ {int (* enum_frame_interval ) (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_frame_interval_enum*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ check_cfg (int /*<<< orphan*/ ,struct v4l2_subdev_pad_config*) ; 
 scalar_t__ check_pad (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 scalar_t__ check_which (int /*<<< orphan*/ ) ; 
 int stub1 (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_frame_interval_enum*) ; 

__attribute__((used)) static int call_enum_frame_interval(struct v4l2_subdev *sd,
				    struct v4l2_subdev_pad_config *cfg,
				    struct v4l2_subdev_frame_interval_enum *fie)
{
	if (!fie)
		return -EINVAL;

	return check_which(fie->which) ? : check_pad(sd, fie->pad) ? :
	       check_cfg(fie->which, cfg) ? :
	       sd->ops->pad->enum_frame_interval(sd, cfg, fie);
}