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
struct uvc_video_queue {int /*<<< orphan*/  mutex; int /*<<< orphan*/  queue; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vb2_streamoff (int /*<<< orphan*/ *,int) ; 

int uvc_queue_streamoff(struct uvc_video_queue *queue, enum v4l2_buf_type type)
{
	int ret;

	mutex_lock(&queue->mutex);
	ret = vb2_streamoff(&queue->queue, type);
	mutex_unlock(&queue->mutex);

	return ret;
}