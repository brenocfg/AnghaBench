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
struct video_device {scalar_t__ ctrl_handler; int /*<<< orphan*/  flags; } ;
struct v4l2_ioctl_ops {int (* vidioc_s_ctrl ) (struct file*,void*,struct v4l2_control*) ;int (* vidioc_s_ext_ctrls ) (struct file*,void*,struct v4l2_ext_controls*) ;} ;
struct v4l2_fh {scalar_t__ ctrl_handler; } ;
struct v4l2_ext_controls {int count; struct v4l2_ext_control* controls; int /*<<< orphan*/  which; } ;
struct v4l2_ext_control {int /*<<< orphan*/  value; int /*<<< orphan*/  id; } ;
struct v4l2_control {int /*<<< orphan*/  value; int /*<<< orphan*/  id; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTTY ; 
 int /*<<< orphan*/  V4L2_CTRL_ID2WHICH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_FL_USES_V4L2_FH ; 
 scalar_t__ check_ext_ctrls (struct v4l2_ext_controls*,int) ; 
 int stub1 (struct file*,void*,struct v4l2_control*) ; 
 int stub2 (struct file*,void*,struct v4l2_ext_controls*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int v4l2_s_ctrl (struct v4l2_fh*,scalar_t__,struct v4l2_control*) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int v4l_s_ctrl(const struct v4l2_ioctl_ops *ops,
				struct file *file, void *fh, void *arg)
{
	struct video_device *vfd = video_devdata(file);
	struct v4l2_control *p = arg;
	struct v4l2_fh *vfh =
		test_bit(V4L2_FL_USES_V4L2_FH, &vfd->flags) ? fh : NULL;
	struct v4l2_ext_controls ctrls;
	struct v4l2_ext_control ctrl;

	if (vfh && vfh->ctrl_handler)
		return v4l2_s_ctrl(vfh, vfh->ctrl_handler, p);
	if (vfd->ctrl_handler)
		return v4l2_s_ctrl(NULL, vfd->ctrl_handler, p);
	if (ops->vidioc_s_ctrl)
		return ops->vidioc_s_ctrl(file, fh, p);
	if (ops->vidioc_s_ext_ctrls == NULL)
		return -ENOTTY;

	ctrls.which = V4L2_CTRL_ID2WHICH(p->id);
	ctrls.count = 1;
	ctrls.controls = &ctrl;
	ctrl.id = p->id;
	ctrl.value = p->value;
	if (check_ext_ctrls(&ctrls, 1))
		return ops->vidioc_s_ext_ctrls(file, fh, &ctrls);
	return -EINVAL;
}