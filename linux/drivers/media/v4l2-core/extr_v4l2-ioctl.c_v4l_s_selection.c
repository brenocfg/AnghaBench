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
typedef  scalar_t__ u32 ;
struct v4l2_selection {scalar_t__ type; } ;
struct v4l2_ioctl_ops {int (* vidioc_s_selection ) (struct file*,void*,struct v4l2_selection*) ;} ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int stub1 (struct file*,void*,struct v4l2_selection*) ; 

__attribute__((used)) static int v4l_s_selection(const struct v4l2_ioctl_ops *ops,
			   struct file *file, void *fh, void *arg)
{
	struct v4l2_selection *p = arg;
	u32 old_type = p->type;
	int ret;

	if (p->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		p->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	else if (p->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		p->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	ret = ops->vidioc_s_selection(file, fh, p);
	p->type = old_type;
	return ret;
}