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
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct via_camera {TYPE_1__ sensor_format; int /*<<< orphan*/  mbus_code; } ;
struct v4l2_subdev_frame_interval_enum {int /*<<< orphan*/  interval; int /*<<< orphan*/  which; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  code; int /*<<< orphan*/  index; } ;
struct v4l2_frmivalenum {scalar_t__ pixel_format; scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  discrete; int /*<<< orphan*/  type; int /*<<< orphan*/  index; } ;
struct file {int dummy; } ;
struct TYPE_4__ {scalar_t__ pixelformat; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int N_VIA_FMTS ; 
 scalar_t__ QCIF_HEIGHT ; 
 scalar_t__ QCIF_WIDTH ; 
 int /*<<< orphan*/  V4L2_FRMIVAL_TYPE_DISCRETE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 scalar_t__ VGA_HEIGHT ; 
 scalar_t__ VGA_WIDTH ; 
 int /*<<< orphan*/  enum_frame_interval ; 
 int /*<<< orphan*/  pad ; 
 int sensor_call (struct via_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_frame_interval_enum*) ; 
 TYPE_2__* via_formats ; 
 struct via_camera* video_drvdata (struct file*) ; 

__attribute__((used)) static int viacam_enum_frameintervals(struct file *filp, void *priv,
		struct v4l2_frmivalenum *interval)
{
	struct via_camera *cam = video_drvdata(filp);
	struct v4l2_subdev_frame_interval_enum fie = {
		.index = interval->index,
		.code = cam->mbus_code,
		.width = cam->sensor_format.width,
		.height = cam->sensor_format.height,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	unsigned int i;
	int ret;

	for (i = 0; i < N_VIA_FMTS; i++)
		if (interval->pixel_format == via_formats[i].pixelformat)
			break;
	if (i >= N_VIA_FMTS)
		return -EINVAL;
	if (interval->width < QCIF_WIDTH || interval->width > VGA_WIDTH ||
	    interval->height < QCIF_HEIGHT || interval->height > VGA_HEIGHT)
		return -EINVAL;
	ret = sensor_call(cam, pad, enum_frame_interval, NULL, &fie);
	if (ret)
		return ret;
	interval->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	interval->discrete = fie.interval;
	return 0;
}