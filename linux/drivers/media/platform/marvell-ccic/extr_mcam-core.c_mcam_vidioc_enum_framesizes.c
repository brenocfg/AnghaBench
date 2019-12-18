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
struct v4l2_subdev_frame_size_enum {scalar_t__ min_width; scalar_t__ max_width; scalar_t__ min_height; scalar_t__ max_height; int /*<<< orphan*/  code; int /*<<< orphan*/  which; int /*<<< orphan*/  index; } ;
struct TYPE_4__ {scalar_t__ min_width; scalar_t__ max_width; scalar_t__ min_height; scalar_t__ max_height; int step_width; int step_height; } ;
struct TYPE_3__ {scalar_t__ width; scalar_t__ height; } ;
struct v4l2_frmsizeenum {scalar_t__ pixel_format; TYPE_2__ stepwise; int /*<<< orphan*/  type; TYPE_1__ discrete; int /*<<< orphan*/  index; } ;
struct mcam_format_struct {scalar_t__ pixelformat; int /*<<< orphan*/  mbus_code; } ;
struct mcam_camera {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_CONTINUOUS ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_DISCRETE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  enum_frame_size ; 
 struct mcam_format_struct* mcam_find_format (scalar_t__) ; 
 int /*<<< orphan*/  pad ; 
 int sensor_call (struct mcam_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_frame_size_enum*) ; 
 struct mcam_camera* video_drvdata (struct file*) ; 

__attribute__((used)) static int mcam_vidioc_enum_framesizes(struct file *filp, void *priv,
		struct v4l2_frmsizeenum *sizes)
{
	struct mcam_camera *cam = video_drvdata(filp);
	struct mcam_format_struct *f;
	struct v4l2_subdev_frame_size_enum fse = {
		.index = sizes->index,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	int ret;

	f = mcam_find_format(sizes->pixel_format);
	if (f->pixelformat != sizes->pixel_format)
		return -EINVAL;
	fse.code = f->mbus_code;
	ret = sensor_call(cam, pad, enum_frame_size, NULL, &fse);
	if (ret)
		return ret;
	if (fse.min_width == fse.max_width &&
	    fse.min_height == fse.max_height) {
		sizes->type = V4L2_FRMSIZE_TYPE_DISCRETE;
		sizes->discrete.width = fse.min_width;
		sizes->discrete.height = fse.min_height;
		return 0;
	}
	sizes->type = V4L2_FRMSIZE_TYPE_CONTINUOUS;
	sizes->stepwise.min_width = fse.min_width;
	sizes->stepwise.max_width = fse.max_width;
	sizes->stepwise.min_height = fse.min_height;
	sizes->stepwise.max_height = fse.max_height;
	sizes->stepwise.step_width = 1;
	sizes->stepwise.step_height = 1;
	return 0;
}