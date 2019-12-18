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
struct vpif_disp_buffer {int /*<<< orphan*/  list; } ;
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct common_obj {int /*<<< orphan*/  irqlock; int /*<<< orphan*/  dma_queue; } ;
struct channel_obj {struct common_obj* common; } ;

/* Variables and functions */
 size_t VPIF_VIDEO_INDEX ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct vpif_disp_buffer* to_vpif_buffer (struct vb2_v4l2_buffer*) ; 
 struct channel_obj* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vpif_buffer_queue(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct vpif_disp_buffer *buf = to_vpif_buffer(vbuf);
	struct channel_obj *ch = vb2_get_drv_priv(vb->vb2_queue);
	struct common_obj *common;
	unsigned long flags;

	common = &ch->common[VPIF_VIDEO_INDEX];

	/* add the buffer to the DMA queue */
	spin_lock_irqsave(&common->irqlock, flags);
	list_add_tail(&buf->list, &common->dma_queue);
	spin_unlock_irqrestore(&common->irqlock, flags);
}