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
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_queue {struct cobalt_stream* drv_priv; } ;
struct vb2_buffer {size_t index; struct vb2_queue* vb2_queue; } ;
struct sg_dma_desc_info {int dummy; } ;
struct cobalt_stream {int /*<<< orphan*/  irqlock; int /*<<< orphan*/  bufs; struct sg_dma_desc_info* dma_desc_info; } ;
struct cobalt_buffer {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  chain_all_buffers (struct cobalt_stream*) ; 
 int /*<<< orphan*/  descriptor_list_interrupt_disable (struct sg_dma_desc_info*) ; 
 int /*<<< orphan*/  descriptor_list_loopback (struct sg_dma_desc_info*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct cobalt_buffer* to_cobalt_buffer (struct vb2_v4l2_buffer*) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 

__attribute__((used)) static void cobalt_buf_queue(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct vb2_queue *q = vb->vb2_queue;
	struct cobalt_stream *s = q->drv_priv;
	struct cobalt_buffer *cb = to_cobalt_buffer(vbuf);
	struct sg_dma_desc_info *desc = &s->dma_desc_info[vb->index];
	unsigned long flags;

	/* Prepare new buffer */
	descriptor_list_loopback(desc);
	descriptor_list_interrupt_disable(desc);

	spin_lock_irqsave(&s->irqlock, flags);
	list_add_tail(&cb->list, &s->bufs);
	chain_all_buffers(s);
	spin_unlock_irqrestore(&s->irqlock, flags);
}