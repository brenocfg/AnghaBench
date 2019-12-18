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
struct vb2_queue {int dummy; } ;
struct uvc_video_queue {int /*<<< orphan*/  irqlock; scalar_t__ buf_used; } ;
struct uvc_streaming {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UVC_BUF_STATE_QUEUED ; 
 int /*<<< orphan*/  lockdep_assert_irqs_enabled () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvc_queue_return_buffers (struct uvc_video_queue*,int /*<<< orphan*/ ) ; 
 struct uvc_streaming* uvc_queue_to_stream (struct uvc_video_queue*) ; 
 int uvc_video_start_streaming (struct uvc_streaming*) ; 
 struct uvc_video_queue* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int uvc_start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct uvc_video_queue *queue = vb2_get_drv_priv(vq);
	struct uvc_streaming *stream = uvc_queue_to_stream(queue);
	int ret;

	lockdep_assert_irqs_enabled();

	queue->buf_used = 0;

	ret = uvc_video_start_streaming(stream);
	if (ret == 0)
		return 0;

	spin_lock_irq(&queue->irqlock);
	uvc_queue_return_buffers(queue, UVC_BUF_STATE_QUEUED);
	spin_unlock_irq(&queue->irqlock);

	return ret;
}