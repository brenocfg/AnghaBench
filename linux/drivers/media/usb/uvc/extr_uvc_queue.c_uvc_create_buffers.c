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
struct v4l2_create_buffers {int dummy; } ;
struct uvc_video_queue {int /*<<< orphan*/  mutex; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vb2_create_bufs (int /*<<< orphan*/ *,struct v4l2_create_buffers*) ; 

int uvc_create_buffers(struct uvc_video_queue *queue,
		       struct v4l2_create_buffers *cb)
{
	int ret;

	mutex_lock(&queue->mutex);
	ret = vb2_create_bufs(&queue->queue, cb);
	mutex_unlock(&queue->mutex);

	return ret;
}