#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct video_device {TYPE_1__* queue; } ;
struct v4l2_requestbuffers {int /*<<< orphan*/  count; int /*<<< orphan*/  memory; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  type; } ;
struct file {int /*<<< orphan*/ * private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * owner; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  fill_buf_caps (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int vb2_core_reqbufs (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vb2_queue_is_busy (struct video_device*,struct file*) ; 
 int vb2_verify_memory_type (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct video_device* video_devdata (struct file*) ; 

int vb2_ioctl_reqbufs(struct file *file, void *priv,
			  struct v4l2_requestbuffers *p)
{
	struct video_device *vdev = video_devdata(file);
	int res = vb2_verify_memory_type(vdev->queue, p->memory, p->type);

	fill_buf_caps(vdev->queue, &p->capabilities);
	if (res)
		return res;
	if (vb2_queue_is_busy(vdev, file))
		return -EBUSY;
	res = vb2_core_reqbufs(vdev->queue, p->memory, &p->count);
	/* If count == 0, then the owner has released all buffers and he
	   is no longer owner of the queue. Otherwise we have a new owner. */
	if (res == 0)
		vdev->queue->owner = p->count ? file->private_data : NULL;
	return res;
}