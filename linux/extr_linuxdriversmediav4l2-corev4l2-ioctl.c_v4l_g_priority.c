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
struct video_device {int /*<<< orphan*/  prio; } ;
struct v4l2_ioctl_ops {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_prio_max (int /*<<< orphan*/ ) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int v4l_g_priority(const struct v4l2_ioctl_ops *ops,
				struct file *file, void *fh, void *arg)
{
	struct video_device *vfd;
	u32 *p = arg;

	vfd = video_devdata(file);
	*p = v4l2_prio_max(vfd->prio);
	return 0;
}