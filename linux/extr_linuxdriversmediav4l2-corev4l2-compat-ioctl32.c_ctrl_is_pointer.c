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
typedef  int /*<<< orphan*/  u32 ;
struct video_device {struct v4l2_ctrl_handler* ctrl_handler; int /*<<< orphan*/  flags; struct v4l2_ioctl_ops* ioctl_ops; } ;
struct v4l2_query_ext_ctrl {int flags; int /*<<< orphan*/  member_0; } ;
struct v4l2_ioctl_ops {int /*<<< orphan*/  (* vidioc_query_ext_ctrl ) (struct file*,struct v4l2_fh*,struct v4l2_query_ext_ctrl*) ;} ;
struct v4l2_fh {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct v4l2_ctrl_handler {int dummy; } ;
struct v4l2_ctrl {scalar_t__ is_ptr; } ;
struct file {struct v4l2_fh* private_data; } ;

/* Variables and functions */
 int V4L2_CTRL_FLAG_HAS_PAYLOAD ; 
 int /*<<< orphan*/  V4L2_FL_USES_V4L2_FH ; 
 int /*<<< orphan*/  stub1 (struct file*,struct v4l2_fh*,struct v4l2_query_ext_ctrl*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct v4l2_ctrl* v4l2_ctrl_find (struct v4l2_ctrl_handler*,int /*<<< orphan*/ ) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static inline bool ctrl_is_pointer(struct file *file, u32 id)
{
	struct video_device *vdev = video_devdata(file);
	struct v4l2_fh *fh = NULL;
	struct v4l2_ctrl_handler *hdl = NULL;
	struct v4l2_query_ext_ctrl qec = { id };
	const struct v4l2_ioctl_ops *ops = vdev->ioctl_ops;

	if (test_bit(V4L2_FL_USES_V4L2_FH, &vdev->flags))
		fh = file->private_data;

	if (fh && fh->ctrl_handler)
		hdl = fh->ctrl_handler;
	else if (vdev->ctrl_handler)
		hdl = vdev->ctrl_handler;

	if (hdl) {
		struct v4l2_ctrl *ctrl = v4l2_ctrl_find(hdl, id);

		return ctrl && ctrl->is_ptr;
	}

	if (!ops || !ops->vidioc_query_ext_ctrl)
		return false;

	return !ops->vidioc_query_ext_ctrl(file, fh, &qec) &&
		(qec.flags & V4L2_CTRL_FLAG_HAS_PAYLOAD);
}