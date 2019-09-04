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
struct isp_prev_device {int dummy; } ;

/* Variables and functions */
 long ENOIOCTLCMD ; 
#define  VIDIOC_OMAP3ISP_PRV_CFG 128 
 long preview_config (struct isp_prev_device*,void*) ; 
 struct isp_prev_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static long preview_ioctl(struct v4l2_subdev *sd, unsigned int cmd, void *arg)
{
	struct isp_prev_device *prev = v4l2_get_subdevdata(sd);

	switch (cmd) {
	case VIDIOC_OMAP3ISP_PRV_CFG:
		return preview_config(prev, arg);

	default:
		return -ENOIOCTLCMD;
	}
}