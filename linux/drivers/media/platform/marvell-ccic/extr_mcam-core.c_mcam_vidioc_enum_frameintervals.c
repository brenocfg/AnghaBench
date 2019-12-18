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
struct v4l2_subdev_frame_interval_enum {int /*<<< orphan*/  interval; int /*<<< orphan*/  code; int /*<<< orphan*/  which; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  index; } ;
struct v4l2_frmivalenum {scalar_t__ pixel_format; int /*<<< orphan*/  discrete; int /*<<< orphan*/  type; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  index; } ;
struct mcam_format_struct {scalar_t__ pixelformat; int /*<<< orphan*/  mbus_code; } ;
struct mcam_camera {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMIVAL_TYPE_DISCRETE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  enum_frame_interval ; 
 struct mcam_format_struct* mcam_find_format (scalar_t__) ; 
 int /*<<< orphan*/  pad ; 
 int sensor_call (struct mcam_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_frame_interval_enum*) ; 
 struct mcam_camera* video_drvdata (struct file*) ; 

__attribute__((used)) static int mcam_vidioc_enum_frameintervals(struct file *filp, void *priv,
		struct v4l2_frmivalenum *interval)
{
	struct mcam_camera *cam = video_drvdata(filp);
	struct mcam_format_struct *f;
	struct v4l2_subdev_frame_interval_enum fie = {
		.index = interval->index,
		.width = interval->width,
		.height = interval->height,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	int ret;

	f = mcam_find_format(interval->pixel_format);
	if (f->pixelformat != interval->pixel_format)
		return -EINVAL;
	fie.code = f->mbus_code;
	ret = sensor_call(cam, pad, enum_frame_interval, NULL, &fie);
	if (ret)
		return ret;
	interval->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	interval->discrete = fie.interval;
	return 0;
}