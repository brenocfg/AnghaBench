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
struct v4l2_subdev_frame_interval_enum {int /*<<< orphan*/  interval; int /*<<< orphan*/  code; int /*<<< orphan*/  which; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  index; } ;
struct v4l2_frmivalenum {int /*<<< orphan*/  discrete; int /*<<< orphan*/  type; int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  index; } ;
struct isc_format {int /*<<< orphan*/  mbus_code; } ;
struct isc_device {TYPE_2__* current_subdev; TYPE_1__* raw_fmt; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sd; } ;
struct TYPE_3__ {int /*<<< orphan*/  mbus_code; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMIVAL_TYPE_DISCRETE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  enum_frame_interval ; 
 struct isc_format* find_format_by_fourcc (struct isc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pad ; 
 scalar_t__ sensor_is_preferred (struct isc_format const*) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_frame_interval_enum*) ; 
 struct isc_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int isc_enum_frameintervals(struct file *file, void *fh,
				    struct v4l2_frmivalenum *fival)
{
	struct isc_device *isc = video_drvdata(file);
	const struct isc_format *isc_fmt;
	struct v4l2_subdev_frame_interval_enum fie = {
		.index = fival->index,
		.width = fival->width,
		.height = fival->height,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	int ret;

	isc_fmt = find_format_by_fourcc(isc, fival->pixel_format);
	if (!isc_fmt)
		return -EINVAL;

	if (sensor_is_preferred(isc_fmt))
		fie.code = isc_fmt->mbus_code;
	else
		fie.code = isc->raw_fmt->mbus_code;

	ret = v4l2_subdev_call(isc->current_subdev->sd, pad,
			       enum_frame_interval, NULL, &fie);
	if (ret)
		return ret;

	fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fival->discrete = fie.interval;

	return 0;
}