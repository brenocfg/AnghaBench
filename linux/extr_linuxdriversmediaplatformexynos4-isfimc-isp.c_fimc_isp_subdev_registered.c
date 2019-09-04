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
struct v4l2_subdev {int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pipe; } ;
struct TYPE_4__ {TYPE_1__ ve; } ;
struct fimc_isp {TYPE_2__ video_capture; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 int fimc_isp_video_device_register (struct fimc_isp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * v4l2_get_subdev_hostdata (struct v4l2_subdev*) ; 
 struct fimc_isp* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int fimc_isp_subdev_registered(struct v4l2_subdev *sd)
{
	struct fimc_isp *isp = v4l2_get_subdevdata(sd);
	int ret;

	/* Use pipeline object allocated by the media device. */
	isp->video_capture.ve.pipe = v4l2_get_subdev_hostdata(sd);

	ret = fimc_isp_video_device_register(isp, sd->v4l2_dev,
			V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);
	if (ret < 0)
		isp->video_capture.ve.pipe = NULL;

	return ret;
}