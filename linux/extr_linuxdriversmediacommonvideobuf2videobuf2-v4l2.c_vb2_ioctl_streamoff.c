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
struct video_device {int /*<<< orphan*/  queue; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ vb2_queue_is_busy (struct video_device*,struct file*) ; 
 int vb2_streamoff (int /*<<< orphan*/ ,int) ; 
 struct video_device* video_devdata (struct file*) ; 

int vb2_ioctl_streamoff(struct file *file, void *priv, enum v4l2_buf_type i)
{
	struct video_device *vdev = video_devdata(file);

	if (vb2_queue_is_busy(vdev, file))
		return -EBUSY;
	return vb2_streamoff(vdev->queue, i);
}