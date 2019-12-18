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
struct uvc_video_queue {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  vb2_queue_release (int /*<<< orphan*/ *) ; 

void uvcg_free_buffers(struct uvc_video_queue *queue)
{
	vb2_queue_release(&queue->queue);
}