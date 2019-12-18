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

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vb2_is_busy (int /*<<< orphan*/ *) ; 

int uvc_queue_allocated(struct uvc_video_queue *queue)
{
	int allocated;

	mutex_lock(&queue->mutex);
	allocated = vb2_is_busy(&queue->queue);
	mutex_unlock(&queue->mutex);

	return allocated;
}