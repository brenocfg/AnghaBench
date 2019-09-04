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
struct vb2_buffer {int /*<<< orphan*/  done_entry; int /*<<< orphan*/  vb2_queue; } ;
struct dt3155_priv {int /*<<< orphan*/  lock; struct vb2_v4l2_buffer* curr_buf; int /*<<< orphan*/  dmaq; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct dt3155_priv* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dt3155_buf_queue(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct dt3155_priv *pd = vb2_get_drv_priv(vb->vb2_queue);

	/*  pd->vidq.streaming = 1 when dt3155_buf_queue() is invoked  */
	spin_lock_irq(&pd->lock);
	if (pd->curr_buf)
		list_add_tail(&vb->done_entry, &pd->dmaq);
	else
		pd->curr_buf = vbuf;
	spin_unlock_irq(&pd->lock);
}