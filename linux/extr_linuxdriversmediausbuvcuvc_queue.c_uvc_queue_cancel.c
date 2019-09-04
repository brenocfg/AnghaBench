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
struct uvc_video_queue {int /*<<< orphan*/  irqlock; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  UVC_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  UVC_QUEUE_DISCONNECTED ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uvc_queue_return_buffers (struct uvc_video_queue*,int /*<<< orphan*/ ) ; 

void uvc_queue_cancel(struct uvc_video_queue *queue, int disconnect)
{
	unsigned long flags;

	spin_lock_irqsave(&queue->irqlock, flags);
	uvc_queue_return_buffers(queue, UVC_BUF_STATE_ERROR);
	/* This must be protected by the irqlock spinlock to avoid race
	 * conditions between uvc_buffer_queue and the disconnection event that
	 * could result in an interruptible wait in uvc_dequeue_buffer. Do not
	 * blindly replace this logic by checking for the UVC_QUEUE_DISCONNECTED
	 * state outside the queue code.
	 */
	if (disconnect)
		queue->flags |= UVC_QUEUE_DISCONNECTED;
	spin_unlock_irqrestore(&queue->irqlock, flags);
}