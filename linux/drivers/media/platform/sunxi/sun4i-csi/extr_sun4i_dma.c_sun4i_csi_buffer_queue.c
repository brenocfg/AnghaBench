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
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct sun4i_csi_buffer {int /*<<< orphan*/  list; } ;
struct sun4i_csi {int /*<<< orphan*/  qlock; int /*<<< orphan*/  buf_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct sun4i_csi* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 struct sun4i_csi_buffer* vb2_to_csi_buffer (struct vb2_buffer*) ; 

__attribute__((used)) static void sun4i_csi_buffer_queue(struct vb2_buffer *vb)
{
	struct sun4i_csi *csi = vb2_get_drv_priv(vb->vb2_queue);
	struct sun4i_csi_buffer *buf = vb2_to_csi_buffer(vb);
	unsigned long flags;

	spin_lock_irqsave(&csi->qlock, flags);
	list_add_tail(&buf->list, &csi->buf_list);
	spin_unlock_irqrestore(&csi->qlock, flags);
}