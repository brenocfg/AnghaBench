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
struct v4l2_ioctl_ops {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENOTTY ; 

__attribute__((used)) static int v4l_dbg_g_register(const struct v4l2_ioctl_ops *ops,
				struct file *file, void *fh, void *arg)
{
#ifdef CONFIG_VIDEO_ADV_DEBUG
	struct v4l2_dbg_register *p = arg;
	struct video_device *vfd = video_devdata(file);
	struct v4l2_subdev *sd;
	int idx = 0;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;
	if (p->match.type == V4L2_CHIP_MATCH_SUBDEV) {
		if (vfd->v4l2_dev == NULL)
			return -EINVAL;
		v4l2_device_for_each_subdev(sd, vfd->v4l2_dev)
			if (p->match.addr == idx++)
				return v4l2_subdev_call(sd, core, g_register, p);
		return -EINVAL;
	}
	if (ops->vidioc_g_register && p->match.type == V4L2_CHIP_MATCH_BRIDGE &&
	    (ops->vidioc_g_chip_info || p->match.addr == 0))
		return ops->vidioc_g_register(file, fh, p);
	return -EINVAL;
#else
	return -ENOTTY;
#endif
}