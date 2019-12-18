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
struct video_device {int dummy; } ;
struct v4l2_ioctl_ops {int (* vidioc_s_input ) (struct file*,void*,unsigned int) ;} ;
struct file {int dummy; } ;

/* Variables and functions */
 int stub1 (struct file*,void*,unsigned int) ; 
 int v4l_enable_media_source (struct video_device*) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int v4l_s_input(const struct v4l2_ioctl_ops *ops,
				struct file *file, void *fh, void *arg)
{
	struct video_device *vfd = video_devdata(file);
	int ret;

	ret = v4l_enable_media_source(vfd);
	if (ret)
		return ret;
	return ops->vidioc_s_input(file, fh, *(unsigned int *)arg);
}