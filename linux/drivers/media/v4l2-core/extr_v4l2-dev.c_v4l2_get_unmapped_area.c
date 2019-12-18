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
struct video_device {int dev_debug; TYPE_1__* fops; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int (* get_unmapped_area ) (struct file*,unsigned long,unsigned long,unsigned long,unsigned long) ;} ;

/* Variables and functions */
 unsigned long ENODEV ; 
 unsigned long ENOSYS ; 
 int V4L2_DEV_DEBUG_FOP ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct file*,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 struct video_device* video_devdata (struct file*) ; 
 int /*<<< orphan*/  video_device_node_name (struct video_device*) ; 
 int /*<<< orphan*/  video_is_registered (struct video_device*) ; 

__attribute__((used)) static unsigned long v4l2_get_unmapped_area(struct file *filp,
		unsigned long addr, unsigned long len, unsigned long pgoff,
		unsigned long flags)
{
	struct video_device *vdev = video_devdata(filp);
	int ret;

	if (!vdev->fops->get_unmapped_area)
		return -ENOSYS;
	if (!video_is_registered(vdev))
		return -ENODEV;
	ret = vdev->fops->get_unmapped_area(filp, addr, len, pgoff, flags);
	if (vdev->dev_debug & V4L2_DEV_DEBUG_FOP)
		dprintk("%s: get_unmapped_area (%d)\n",
			video_device_node_name(vdev), ret);
	return ret;
}