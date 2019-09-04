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
struct v4l2_exportbuffer {int dummy; } ;
struct uvc_video_queue {int /*<<< orphan*/  mutex; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vb2_expbuf (int /*<<< orphan*/ *,struct v4l2_exportbuffer*) ; 

int uvc_export_buffer(struct uvc_video_queue *queue,
		      struct v4l2_exportbuffer *exp)
{
	int ret;

	mutex_lock(&queue->mutex);
	ret = vb2_expbuf(&queue->queue, exp);
	mutex_unlock(&queue->mutex);

	return ret;
}