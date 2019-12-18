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
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct ceu_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  capture; } ;
struct ceu_buffer {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct ceu_device* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 struct ceu_buffer* vb2_to_ceu (struct vb2_v4l2_buffer*) ; 

__attribute__((used)) static void ceu_vb2_queue(struct vb2_buffer *vb)
{
	struct ceu_device *ceudev = vb2_get_drv_priv(vb->vb2_queue);
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct ceu_buffer *buf = vb2_to_ceu(vbuf);
	unsigned long irqflags;

	spin_lock_irqsave(&ceudev->lock, irqflags);
	list_add_tail(&buf->queue, &ceudev->capture);
	spin_unlock_irqrestore(&ceudev->lock, irqflags);
}