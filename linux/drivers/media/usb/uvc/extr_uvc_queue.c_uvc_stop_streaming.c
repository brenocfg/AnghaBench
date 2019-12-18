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
struct vb2_queue {scalar_t__ type; } ;
struct uvc_video_queue {int /*<<< orphan*/  irqlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  UVC_BUF_STATE_ERROR ; 
 scalar_t__ V4L2_BUF_TYPE_META_CAPTURE ; 
 int /*<<< orphan*/  lockdep_assert_irqs_enabled () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvc_queue_return_buffers (struct uvc_video_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_queue_to_stream (struct uvc_video_queue*) ; 
 int /*<<< orphan*/  uvc_video_stop_streaming (int /*<<< orphan*/ ) ; 
 struct uvc_video_queue* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void uvc_stop_streaming(struct vb2_queue *vq)
{
	struct uvc_video_queue *queue = vb2_get_drv_priv(vq);

	lockdep_assert_irqs_enabled();

	if (vq->type != V4L2_BUF_TYPE_META_CAPTURE)
		uvc_video_stop_streaming(uvc_queue_to_stream(queue));

	spin_lock_irq(&queue->irqlock);
	uvc_queue_return_buffers(queue, UVC_BUF_STATE_ERROR);
	spin_unlock_irq(&queue->irqlock);
}