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
struct video_device {int device_caps; } ;
struct v4l2_ioctl_ops {int (* vidioc_querycap ) (struct file*,void*,struct v4l2_capability*) ;} ;
struct v4l2_capability {int device_caps; int capabilities; int /*<<< orphan*/  version; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_VERSION_CODE ; 
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_EXT_PIX_FORMAT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int stub1 (struct file*,void*,struct v4l2_capability*) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int v4l_querycap(const struct v4l2_ioctl_ops *ops,
				struct file *file, void *fh, void *arg)
{
	struct v4l2_capability *cap = (struct v4l2_capability *)arg;
	struct video_device *vfd = video_devdata(file);
	int ret;

	cap->version = LINUX_VERSION_CODE;
	cap->device_caps = vfd->device_caps;
	cap->capabilities = vfd->device_caps | V4L2_CAP_DEVICE_CAPS;

	ret = ops->vidioc_querycap(file, fh, cap);

	/*
	 * Drivers must not change device_caps, so check for this and
	 * warn if this happened.
	 */
	WARN_ON(cap->device_caps != vfd->device_caps);
	/*
	 * Check that capabilities is a superset of
	 * vfd->device_caps | V4L2_CAP_DEVICE_CAPS
	 */
	WARN_ON((cap->capabilities &
		 (vfd->device_caps | V4L2_CAP_DEVICE_CAPS)) !=
		(vfd->device_caps | V4L2_CAP_DEVICE_CAPS));
	cap->capabilities |= V4L2_CAP_EXT_PIX_FORMAT;
	cap->device_caps |= V4L2_CAP_EXT_PIX_FORMAT;

	return ret;
}