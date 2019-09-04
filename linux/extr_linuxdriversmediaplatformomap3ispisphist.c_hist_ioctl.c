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
struct ispstat {int dummy; } ;

/* Variables and functions */
 long ENOIOCTLCMD ; 
#define  VIDIOC_OMAP3ISP_HIST_CFG 131 
#define  VIDIOC_OMAP3ISP_STAT_EN 130 
#define  VIDIOC_OMAP3ISP_STAT_REQ 129 
#define  VIDIOC_OMAP3ISP_STAT_REQ_TIME32 128 
 long omap3isp_stat_config (struct ispstat*,void*) ; 
 long omap3isp_stat_enable (struct ispstat*,int) ; 
 long omap3isp_stat_request_statistics (struct ispstat*,void*) ; 
 long omap3isp_stat_request_statistics_time32 (struct ispstat*,void*) ; 
 struct ispstat* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static long hist_ioctl(struct v4l2_subdev *sd, unsigned int cmd, void *arg)
{
	struct ispstat *stat = v4l2_get_subdevdata(sd);

	switch (cmd) {
	case VIDIOC_OMAP3ISP_HIST_CFG:
		return omap3isp_stat_config(stat, arg);
	case VIDIOC_OMAP3ISP_STAT_REQ:
		return omap3isp_stat_request_statistics(stat, arg);
	case VIDIOC_OMAP3ISP_STAT_REQ_TIME32:
		return omap3isp_stat_request_statistics_time32(stat, arg);
	case VIDIOC_OMAP3ISP_STAT_EN: {
		int *en = arg;
		return omap3isp_stat_enable(stat, !!*en);
	}
	}

	return -ENOIOCTLCMD;

}