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
struct v4l2_exportbuffer {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int vb2_expbuf (int /*<<< orphan*/ ,struct v4l2_exportbuffer*) ; 
 scalar_t__ vb2_queue_is_busy (struct video_device*,struct file*) ; 
 struct video_device* video_devdata (struct file*) ; 

int vb2_ioctl_expbuf(struct file *file, void *priv, struct v4l2_exportbuffer *p)
{
	struct video_device *vdev = video_devdata(file);

	if (vb2_queue_is_busy(vdev, file))
		return -EBUSY;
	return vb2_expbuf(vdev->queue, p);
}