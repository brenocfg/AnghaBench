#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct video_device {TYPE_2__* queue; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct v4l2_create_buffers {scalar_t__ count; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  index; TYPE_1__ format; int /*<<< orphan*/  memory; } ;
struct file {int /*<<< orphan*/  private_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  num_buffers; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  fill_buf_caps (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int vb2_create_bufs (TYPE_2__*,struct v4l2_create_buffers*) ; 
 scalar_t__ vb2_queue_is_busy (struct video_device*,struct file*) ; 
 int vb2_verify_memory_type (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct video_device* video_devdata (struct file*) ; 

int vb2_ioctl_create_bufs(struct file *file, void *priv,
			  struct v4l2_create_buffers *p)
{
	struct video_device *vdev = video_devdata(file);
	int res = vb2_verify_memory_type(vdev->queue, p->memory,
			p->format.type);

	p->index = vdev->queue->num_buffers;
	fill_buf_caps(vdev->queue, &p->capabilities);
	/*
	 * If count == 0, then just check if memory and type are valid.
	 * Any -EBUSY result from vb2_verify_memory_type can be mapped to 0.
	 */
	if (p->count == 0)
		return res != -EBUSY ? res : 0;
	if (res)
		return res;
	if (vb2_queue_is_busy(vdev, file))
		return -EBUSY;

	res = vb2_create_bufs(vdev->queue, p);
	if (res == 0)
		vdev->queue->owner = file->private_data;
	return res;
}