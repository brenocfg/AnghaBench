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
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct via_camera {int /*<<< orphan*/  lock; TYPE_1__ sensor_format; int /*<<< orphan*/  mbus_code; } ;
struct v4l2_subdev_frame_interval_enum {int /*<<< orphan*/  interval; int /*<<< orphan*/  which; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  code; int /*<<< orphan*/  index; } ;
struct v4l2_frmivalenum {int /*<<< orphan*/  discrete; int /*<<< orphan*/  type; int /*<<< orphan*/  index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FRMIVAL_TYPE_DISCRETE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  enum_frame_interval ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pad ; 
 int sensor_call (struct via_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_frame_interval_enum*) ; 

__attribute__((used)) static int viacam_enum_frameintervals(struct file *filp, void *priv,
		struct v4l2_frmivalenum *interval)
{
	struct via_camera *cam = priv;
	struct v4l2_subdev_frame_interval_enum fie = {
		.index = interval->index,
		.code = cam->mbus_code,
		.width = cam->sensor_format.width,
		.height = cam->sensor_format.height,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	int ret;

	mutex_lock(&cam->lock);
	ret = sensor_call(cam, pad, enum_frame_interval, NULL, &fie);
	mutex_unlock(&cam->lock);
	if (ret)
		return ret;
	interval->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	interval->discrete = fie.interval;
	return 0;
}