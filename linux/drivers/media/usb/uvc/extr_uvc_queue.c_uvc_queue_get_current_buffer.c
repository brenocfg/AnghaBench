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
struct uvc_video_queue {int /*<<< orphan*/  irqlock; } ;
struct uvc_buffer {int dummy; } ;

/* Variables and functions */
 struct uvc_buffer* __uvc_queue_get_current_buffer (struct uvc_video_queue*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct uvc_buffer *uvc_queue_get_current_buffer(struct uvc_video_queue *queue)
{
	struct uvc_buffer *nextbuf;
	unsigned long flags;

	spin_lock_irqsave(&queue->irqlock, flags);
	nextbuf = __uvc_queue_get_current_buffer(queue);
	spin_unlock_irqrestore(&queue->irqlock, flags);

	return nextbuf;
}