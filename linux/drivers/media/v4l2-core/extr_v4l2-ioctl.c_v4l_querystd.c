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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct video_device {int /*<<< orphan*/  tvnorms; } ;
struct v4l2_ioctl_ops {int (* vidioc_querystd ) (struct file*,void*,void*) ;} ;
struct file {int dummy; } ;

/* Variables and functions */
 int stub1 (struct file*,void*,void*) ; 
 int v4l_enable_media_source (struct video_device*) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int v4l_querystd(const struct v4l2_ioctl_ops *ops,
				struct file *file, void *fh, void *arg)
{
	struct video_device *vfd = video_devdata(file);
	v4l2_std_id *p = arg;
	int ret;

	ret = v4l_enable_media_source(vfd);
	if (ret)
		return ret;
	/*
	 * If no signal is detected, then the driver should return
	 * V4L2_STD_UNKNOWN. Otherwise it should return tvnorms with
	 * any standards that do not apply removed.
	 *
	 * This means that tuners, audio and video decoders can join
	 * their efforts to improve the standards detection.
	 */
	*p = vfd->tvnorms;
	return ops->vidioc_querystd(file, fh, arg);
}