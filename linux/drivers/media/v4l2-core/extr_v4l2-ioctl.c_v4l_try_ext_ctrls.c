#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct video_device {TYPE_1__* v4l2_dev; scalar_t__ ctrl_handler; int /*<<< orphan*/  flags; } ;
struct v4l2_ioctl_ops {int (* vidioc_try_ext_ctrls ) (struct file*,void*,struct v4l2_ext_controls*) ;} ;
struct v4l2_fh {scalar_t__ ctrl_handler; } ;
struct v4l2_ext_controls {int /*<<< orphan*/  count; int /*<<< orphan*/  error_idx; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTTY ; 
 int /*<<< orphan*/  V4L2_FL_USES_V4L2_FH ; 
 scalar_t__ check_ext_ctrls (struct v4l2_ext_controls*,int /*<<< orphan*/ ) ; 
 int stub1 (struct file*,void*,struct v4l2_ext_controls*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int v4l2_try_ext_ctrls (scalar_t__,struct video_device*,int /*<<< orphan*/ ,struct v4l2_ext_controls*) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int v4l_try_ext_ctrls(const struct v4l2_ioctl_ops *ops,
				struct file *file, void *fh, void *arg)
{
	struct video_device *vfd = video_devdata(file);
	struct v4l2_ext_controls *p = arg;
	struct v4l2_fh *vfh =
		test_bit(V4L2_FL_USES_V4L2_FH, &vfd->flags) ? fh : NULL;

	p->error_idx = p->count;
	if (vfh && vfh->ctrl_handler)
		return v4l2_try_ext_ctrls(vfh->ctrl_handler,
					  vfd, vfd->v4l2_dev->mdev, p);
	if (vfd->ctrl_handler)
		return v4l2_try_ext_ctrls(vfd->ctrl_handler,
					  vfd, vfd->v4l2_dev->mdev, p);
	if (ops->vidioc_try_ext_ctrls == NULL)
		return -ENOTTY;
	return check_ext_ctrls(p, 0) ? ops->vidioc_try_ext_ctrls(file, fh, p) :
					-EINVAL;
}