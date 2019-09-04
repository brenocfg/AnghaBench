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
struct video_device {int /*<<< orphan*/  prio; int /*<<< orphan*/  flags; } ;
struct v4l2_ioctl_ops {int dummy; } ;
struct v4l2_fh {int /*<<< orphan*/  prio; } ;
struct file {struct v4l2_fh* private_data; } ;

/* Variables and functions */
 int ENOTTY ; 
 int /*<<< orphan*/  V4L2_FL_USES_V4L2_FH ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int v4l2_prio_change (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int v4l_s_priority(const struct v4l2_ioctl_ops *ops,
				struct file *file, void *fh, void *arg)
{
	struct video_device *vfd;
	struct v4l2_fh *vfh;
	u32 *p = arg;

	vfd = video_devdata(file);
	if (!test_bit(V4L2_FL_USES_V4L2_FH, &vfd->flags))
		return -ENOTTY;
	vfh = file->private_data;
	return v4l2_prio_change(vfd->prio, &vfh->prio, *p);
}