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
struct gspca_dev {int /*<<< orphan*/  qlock; int /*<<< orphan*/  buf_list; } ;
struct gspca_buffer {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct gspca_buffer* to_gspca_buffer (struct vb2_buffer*) ; 
 struct gspca_dev* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gspca_buffer_queue(struct vb2_buffer *vb)
{
	struct gspca_dev *gspca_dev = vb2_get_drv_priv(vb->vb2_queue);
	struct gspca_buffer *buf = to_gspca_buffer(vb);
	unsigned long flags;

	spin_lock_irqsave(&gspca_dev->qlock, flags);
	list_add_tail(&buf->list, &gspca_dev->buf_list);
	spin_unlock_irqrestore(&gspca_dev->qlock, flags);
}