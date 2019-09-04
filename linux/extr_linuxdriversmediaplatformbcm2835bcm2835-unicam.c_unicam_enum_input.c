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
struct v4l2_input {scalar_t__ index; int /*<<< orphan*/  name; scalar_t__ std; scalar_t__ capabilities; int /*<<< orphan*/  type; } ;
struct unicam_device {int /*<<< orphan*/  sensor; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 scalar_t__ V4L2_IN_CAP_DV_TIMINGS ; 
 scalar_t__ V4L2_IN_CAP_STD ; 
 scalar_t__ V4L2_STD_ALL ; 
 int /*<<< orphan*/  g_tvnorms ; 
 int /*<<< orphan*/  s_dv_timings ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ v4l2_subdev_has_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 
 struct unicam_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int unicam_enum_input(struct file *file, void *priv,
			     struct v4l2_input *inp)
{
	struct unicam_device *dev = video_drvdata(file);

	if (inp->index != 0)
		return -EINVAL;

	inp->type = V4L2_INPUT_TYPE_CAMERA;
	if (v4l2_subdev_has_op(dev->sensor, video, s_dv_timings)) {
		inp->capabilities = V4L2_IN_CAP_DV_TIMINGS;
		inp->std = 0;
	} else if (v4l2_subdev_has_op(dev->sensor, video, s_std)) {
		inp->capabilities = V4L2_IN_CAP_STD;
		if (v4l2_subdev_call(dev->sensor, video, g_tvnorms, &inp->std)
					< 0)
			inp->std = V4L2_STD_ALL;
	} else {
		inp->capabilities = 0;
		inp->std = 0;
	}
	sprintf(inp->name, "Camera 0");
	return 0;
}