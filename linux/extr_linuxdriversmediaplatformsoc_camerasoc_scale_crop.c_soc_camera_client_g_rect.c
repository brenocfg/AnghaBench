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
struct v4l2_rect {int dummy; } ;
struct v4l2_subdev_selection {struct v4l2_rect r; int /*<<< orphan*/  target; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_SEL_TGT_CROP ; 
 int /*<<< orphan*/  V4L2_SEL_TGT_CROP_DEFAULT ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  get_selection ; 
 int /*<<< orphan*/  pad ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_selection*) ; 

int soc_camera_client_g_rect(struct v4l2_subdev *sd, struct v4l2_rect *rect)
{
	struct v4l2_subdev_selection sdsel = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.target = V4L2_SEL_TGT_CROP,
	};
	int ret;

	ret = v4l2_subdev_call(sd, pad, get_selection, NULL, &sdsel);
	if (!ret) {
		*rect = sdsel.r;
		return ret;
	}

	sdsel.target = V4L2_SEL_TGT_CROP_DEFAULT;
	ret = v4l2_subdev_call(sd, pad, get_selection, NULL, &sdsel);
	if (!ret)
		*rect = sdsel.r;

	return ret;
}