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
struct v4l2_subdev_frame_interval_enum {int /*<<< orphan*/  interval; int /*<<< orphan*/  which; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  index; int /*<<< orphan*/  code; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_frmivalenum {int /*<<< orphan*/  discrete; int /*<<< orphan*/  type; int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  index; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mbus_code; } ;
struct ceu_subdev {TYPE_1__ mbus_fmt; struct v4l2_subdev* v4l2_sd; } ;
struct ceu_fmt {int dummy; } ;
struct ceu_device {struct ceu_subdev* sd; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMIVAL_TYPE_DISCRETE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  enum_frame_interval ; 
 struct ceu_fmt* get_ceu_fmt_from_fourcc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pad ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_frame_interval_enum*) ; 
 struct ceu_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int ceu_enum_frameintervals(struct file *file, void *fh,
				   struct v4l2_frmivalenum *fival)
{
	struct ceu_device *ceudev = video_drvdata(file);
	struct ceu_subdev *ceu_sd = ceudev->sd;
	const struct ceu_fmt *ceu_fmt;
	struct v4l2_subdev *v4l2_sd = ceu_sd->v4l2_sd;
	int ret;

	struct v4l2_subdev_frame_interval_enum fie = {
		.code	= ceu_sd->mbus_fmt.mbus_code,
		.index = fival->index,
		.width = fival->width,
		.height = fival->height,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};

	/* Just check if user supplied pixel format is supported. */
	ceu_fmt = get_ceu_fmt_from_fourcc(fival->pixel_format);
	if (!ceu_fmt)
		return -EINVAL;

	ret = v4l2_subdev_call(v4l2_sd, pad, enum_frame_interval, NULL,
			       &fie);
	if (ret)
		return ret;

	fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fival->discrete = fie.interval;

	return 0;
}