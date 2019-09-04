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
struct video_device {scalar_t__ vfl_type; } ;
struct v4l2_modulator {int /*<<< orphan*/  type; } ;
struct v4l2_ioctl_ops {int (* vidioc_s_modulator ) (struct file*,void*,struct v4l2_modulator*) ;} ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 scalar_t__ VFL_TYPE_RADIO ; 
 int stub1 (struct file*,void*,struct v4l2_modulator*) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int v4l_s_modulator(const struct v4l2_ioctl_ops *ops,
				struct file *file, void *fh, void *arg)
{
	struct video_device *vfd = video_devdata(file);
	struct v4l2_modulator *p = arg;

	if (vfd->vfl_type == VFL_TYPE_RADIO)
		p->type = V4L2_TUNER_RADIO;

	return ops->vidioc_s_modulator(file, fh, p);
}