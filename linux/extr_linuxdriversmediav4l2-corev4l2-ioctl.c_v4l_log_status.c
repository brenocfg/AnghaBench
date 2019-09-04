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
struct video_device {TYPE_1__* v4l2_dev; } ;
struct v4l2_ioctl_ops {int (* vidioc_log_status ) (struct file*,void*) ;} ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct file*,void*) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int v4l_log_status(const struct v4l2_ioctl_ops *ops,
				struct file *file, void *fh, void *arg)
{
	struct video_device *vfd = video_devdata(file);
	int ret;

	if (vfd->v4l2_dev)
		pr_info("%s: =================  START STATUS  =================\n",
			vfd->v4l2_dev->name);
	ret = ops->vidioc_log_status(file, fh);
	if (vfd->v4l2_dev)
		pr_info("%s: ==================  END STATUS  ==================\n",
			vfd->v4l2_dev->name);
	return ret;
}