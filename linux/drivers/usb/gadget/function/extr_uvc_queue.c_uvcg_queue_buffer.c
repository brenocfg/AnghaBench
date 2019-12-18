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
struct uvc_video_queue {int flags; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int UVC_QUEUE_PAUSED ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int vb2_qbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct v4l2_buffer*) ; 

int uvcg_queue_buffer(struct uvc_video_queue *queue, struct v4l2_buffer *buf)
{
	unsigned long flags;
	int ret;

	ret = vb2_qbuf(&queue->queue, NULL, buf);
	if (ret < 0)
		return ret;

	spin_lock_irqsave(&queue->irqlock, flags);
	ret = (queue->flags & UVC_QUEUE_PAUSED) != 0;
	queue->flags &= ~UVC_QUEUE_PAUSED;
	spin_unlock_irqrestore(&queue->irqlock, flags);
	return ret;
}