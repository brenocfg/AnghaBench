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
struct vpif_cap_buffer {int /*<<< orphan*/  list; } ;
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct common_obj {int /*<<< orphan*/  irqlock; int /*<<< orphan*/  dma_queue; } ;
struct channel_obj {struct common_obj* common; } ;

/* Variables and functions */
 size_t VPIF_VIDEO_INDEX ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct vpif_cap_buffer* to_vpif_buffer (struct vb2_v4l2_buffer*) ; 
 struct channel_obj* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void vpif_buffer_queue(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct channel_obj *ch = vb2_get_drv_priv(vb->vb2_queue);
	struct vpif_cap_buffer *buf = to_vpif_buffer(vbuf);
	struct common_obj *common;
	unsigned long flags;

	common = &ch->common[VPIF_VIDEO_INDEX];

	vpif_dbg(2, debug, "vpif_buffer_queue\n");

	spin_lock_irqsave(&common->irqlock, flags);
	/* add the buffer to the DMA queue */
	list_add_tail(&buf->list, &common->dma_queue);
	spin_unlock_irqrestore(&common->irqlock, flags);
}