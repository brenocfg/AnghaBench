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

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vb2_dqbuf (int /*<<< orphan*/ *,struct v4l2_buffer*,int) ; 

int uvc_dequeue_buffer(struct uvc_video_queue *queue, struct v4l2_buffer *buf,
		       int nonblocking)
{
	int ret;

	mutex_lock(&queue->mutex);
	ret = vb2_dqbuf(&queue->queue, buf, nonblocking);
	mutex_unlock(&queue->mutex);

	return ret;
}