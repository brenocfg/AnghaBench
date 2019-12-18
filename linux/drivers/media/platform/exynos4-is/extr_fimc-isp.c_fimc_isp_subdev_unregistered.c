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
struct v4l2_subdev {int dummy; } ;
struct fimc_isp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 int /*<<< orphan*/  fimc_isp_video_device_unregister (struct fimc_isp*,int /*<<< orphan*/ ) ; 
 struct fimc_isp* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static void fimc_isp_subdev_unregistered(struct v4l2_subdev *sd)
{
	struct fimc_isp *isp = v4l2_get_subdevdata(sd);

	fimc_isp_video_device_unregister(isp,
			V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);
}