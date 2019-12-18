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
struct v4l2_buffer {int dummy; } ;
struct uvc_video_queue {int /*<<< orphan*/  mutex; int /*<<< orphan*/  queue; } ;
struct media_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vb2_qbuf (int /*<<< orphan*/ *,struct media_device*,struct v4l2_buffer*) ; 

int uvc_queue_buffer(struct uvc_video_queue *queue,
		     struct media_device *mdev, struct v4l2_buffer *buf)
{
	int ret;

	mutex_lock(&queue->mutex);
	ret = vb2_qbuf(&queue->queue, mdev, buf);
	mutex_unlock(&queue->mutex);

	return ret;
}