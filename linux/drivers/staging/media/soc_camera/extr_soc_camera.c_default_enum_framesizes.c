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
struct v4l2_subdev {int dummy; } ;
struct TYPE_4__ {scalar_t__ min_width; scalar_t__ max_width; scalar_t__ min_height; scalar_t__ max_height; int step_width; int step_height; } ;
struct TYPE_3__ {scalar_t__ width; scalar_t__ height; } ;
struct v4l2_frmsizeenum {TYPE_2__ stepwise; int /*<<< orphan*/  type; TYPE_1__ discrete; int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  index; } ;
struct soc_camera_format_xlate {int /*<<< orphan*/  code; } ;
struct soc_camera_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_CONTINUOUS ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_DISCRETE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  enum_frame_size ; 
 int /*<<< orphan*/  pad ; 
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 
 struct soc_camera_format_xlate* soc_camera_xlate_by_fourcc (struct soc_camera_device*,int /*<<< orphan*/ ) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_frame_size_enum*) ; 

__attribute__((used)) static int default_enum_framesizes(struct soc_camera_device *icd,
				   struct v4l2_frmsizeenum *fsize)
{
	int ret;
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	const struct soc_camera_format_xlate *xlate;
	struct v4l2_subdev_frame_size_enum fse = {
		.index = fsize->index,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};

	xlate = soc_camera_xlate_by_fourcc(icd, fsize->pixel_format);
	if (!xlate)
		return -EINVAL;
	fse.code = xlate->code;

	ret = v4l2_subdev_call(sd, pad, enum_frame_size, NULL, &fse);
	if (ret < 0)
		return ret;

	if (fse.min_width == fse.max_width &&
	    fse.min_height == fse.max_height) {
		fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
		fsize->discrete.width = fse.min_width;
		fsize->discrete.height = fse.min_height;
		return 0;
	}
	fsize->type = V4L2_FRMSIZE_TYPE_CONTINUOUS;
	fsize->stepwise.min_width = fse.min_width;
	fsize->stepwise.max_width = fse.max_width;
	fsize->stepwise.min_height = fse.min_height;
	fsize->stepwise.max_height = fse.max_height;
	fsize->stepwise.step_width = 1;
	fsize->stepwise.step_height = 1;
	return 0;
}