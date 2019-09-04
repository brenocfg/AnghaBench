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
struct v4l2_ioctl_ops {int (* vidioc_enum_input ) (struct file*,void*,struct v4l2_input*) ;} ;
struct v4l2_input {int /*<<< orphan*/  capabilities; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_IN_CAP_STD ; 
 int /*<<< orphan*/  VIDIOC_S_STD ; 
 scalar_t__ is_valid_ioctl (struct video_device*,int /*<<< orphan*/ ) ; 
 int stub1 (struct file*,void*,struct v4l2_input*) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int v4l_enuminput(const struct v4l2_ioctl_ops *ops,
				struct file *file, void *fh, void *arg)
{
	struct video_device *vfd = video_devdata(file);
	struct v4l2_input *p = arg;

	/*
	 * We set the flags for CAP_DV_TIMINGS &
	 * CAP_STD here based on ioctl handler provided by the
	 * driver. If the driver doesn't support these
	 * for a specific input, it must override these flags.
	 */
	if (is_valid_ioctl(vfd, VIDIOC_S_STD))
		p->capabilities |= V4L2_IN_CAP_STD;

	return ops->vidioc_enum_input(file, fh, p);
}