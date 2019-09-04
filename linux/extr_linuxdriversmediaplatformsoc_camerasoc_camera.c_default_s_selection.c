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
struct v4l2_subdev_selection {int /*<<< orphan*/  r; int /*<<< orphan*/  flags; int /*<<< orphan*/  target; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_selection {int /*<<< orphan*/  r; int /*<<< orphan*/  flags; int /*<<< orphan*/  target; } ;
struct soc_camera_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  set_selection ; 
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_selection*) ; 

__attribute__((used)) static int default_s_selection(struct soc_camera_device *icd,
			       struct v4l2_selection *sel)
{
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	struct v4l2_subdev_selection sdsel = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.target = sel->target,
		.flags = sel->flags,
		.r = sel->r,
	};
	int ret;

	ret = v4l2_subdev_call(sd, pad, set_selection, NULL, &sdsel);
	if (ret)
		return ret;
	sel->r = sdsel.r;
	return 0;
}