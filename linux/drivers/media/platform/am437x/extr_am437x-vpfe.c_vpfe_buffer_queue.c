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
struct vpfe_device {int /*<<< orphan*/  dma_queue_lock; int /*<<< orphan*/  dma_queue; } ;
struct vpfe_cap_buffer {int /*<<< orphan*/  list; } ;
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct vpfe_cap_buffer* to_vpfe_buffer (struct vb2_v4l2_buffer*) ; 
 struct vpfe_device* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vpfe_buffer_queue(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct vpfe_device *vpfe = vb2_get_drv_priv(vb->vb2_queue);
	struct vpfe_cap_buffer *buf = to_vpfe_buffer(vbuf);
	unsigned long flags = 0;

	/* add the buffer to the DMA queue */
	spin_lock_irqsave(&vpfe->dma_queue_lock, flags);
	list_add_tail(&buf->list, &vpfe->dma_queue);
	spin_unlock_irqrestore(&vpfe->dma_queue_lock, flags);
}