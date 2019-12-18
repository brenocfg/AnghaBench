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
struct video_device {TYPE_1__* v4l2_dev; int /*<<< orphan*/  queue; } ;
struct v4l2_buffer {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int vb2_prepare_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_buffer*) ; 
 scalar_t__ vb2_queue_is_busy (struct video_device*,struct file*) ; 
 struct video_device* video_devdata (struct file*) ; 

int vb2_ioctl_prepare_buf(struct file *file, void *priv,
			  struct v4l2_buffer *p)
{
	struct video_device *vdev = video_devdata(file);

	if (vb2_queue_is_busy(vdev, file))
		return -EBUSY;
	return vb2_prepare_buf(vdev->queue, vdev->v4l2_dev->mdev, p);
}