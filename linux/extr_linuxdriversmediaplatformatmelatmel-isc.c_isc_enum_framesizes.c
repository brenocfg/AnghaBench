#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev_frame_size_enum {int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  code; int /*<<< orphan*/  which; int /*<<< orphan*/  index; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_frmsizeenum {TYPE_3__ discrete; int /*<<< orphan*/  type; int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  index; } ;
struct isc_format {int /*<<< orphan*/  mbus_code; } ;
struct isc_device {TYPE_2__* current_subdev; TYPE_1__* raw_fmt; } ;
struct file {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  sd; } ;
struct TYPE_4__ {int /*<<< orphan*/  mbus_code; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_DISCRETE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  enum_frame_size ; 
 struct isc_format* find_format_by_fourcc (struct isc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pad ; 
 scalar_t__ sensor_is_preferred (struct isc_format const*) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_frame_size_enum*) ; 
 struct isc_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int isc_enum_framesizes(struct file *file, void *fh,
			       struct v4l2_frmsizeenum *fsize)
{
	struct isc_device *isc = video_drvdata(file);
	const struct isc_format *isc_fmt;
	struct v4l2_subdev_frame_size_enum fse = {
		.index = fsize->index,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	int ret;

	isc_fmt = find_format_by_fourcc(isc, fsize->pixel_format);
	if (!isc_fmt)
		return -EINVAL;

	if (sensor_is_preferred(isc_fmt))
		fse.code = isc_fmt->mbus_code;
	else
		fse.code = isc->raw_fmt->mbus_code;

	ret = v4l2_subdev_call(isc->current_subdev->sd, pad, enum_frame_size,
			       NULL, &fse);
	if (ret)
		return ret;

	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = fse.max_width;
	fsize->discrete.height = fse.max_height;

	return 0;
}