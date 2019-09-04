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
struct v4l2_subdev_format {int /*<<< orphan*/  format; int /*<<< orphan*/  which; } ;
struct mcam_camera {int /*<<< orphan*/  mbus_code; int /*<<< orphan*/  pix_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  init ; 
 scalar_t__ mcam_cam_set_flip (struct mcam_camera*) ; 
 int /*<<< orphan*/  pad ; 
 int sensor_call (struct mcam_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  set_fmt ; 
 int /*<<< orphan*/  v4l2_fill_mbus_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcam_cam_configure(struct mcam_camera *cam)
{
	struct v4l2_subdev_format format = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	int ret;

	v4l2_fill_mbus_format(&format.format, &cam->pix_format, cam->mbus_code);
	ret = sensor_call(cam, core, init, 0);
	if (ret == 0)
		ret = sensor_call(cam, pad, set_fmt, NULL, &format);
	/*
	 * OV7670 does weird things if flip is set *before* format...
	 */
	ret += mcam_cam_set_flip(cam);
	return ret;
}