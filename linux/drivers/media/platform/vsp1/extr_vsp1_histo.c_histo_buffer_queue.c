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
struct vsp1_histogram_buffer {int /*<<< orphan*/  queue; } ;
struct vsp1_histogram {int /*<<< orphan*/  irqlock; int /*<<< orphan*/  irqqueue; } ;
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct vsp1_histogram_buffer* to_vsp1_histogram_buffer (struct vb2_v4l2_buffer*) ; 
 struct vsp1_histogram* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void histo_buffer_queue(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct vsp1_histogram *histo = vb2_get_drv_priv(vb->vb2_queue);
	struct vsp1_histogram_buffer *buf = to_vsp1_histogram_buffer(vbuf);
	unsigned long flags;

	spin_lock_irqsave(&histo->irqlock, flags);
	list_add_tail(&buf->queue, &histo->irqqueue);
	spin_unlock_irqrestore(&histo->irqlock, flags);
}