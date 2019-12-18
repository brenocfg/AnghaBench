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
struct inode {int dummy; } ;
struct file {scalar_t__ private_data; } ;
struct eerbuffer {struct eerbuffer* buffer; int /*<<< orphan*/  buffer_page_count; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  bufferlock ; 
 int /*<<< orphan*/  dasd_eer_free_buffer_pages (struct eerbuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct eerbuffer*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dasd_eer_close(struct inode *inp, struct file *filp)
{
	struct eerbuffer *eerb;
	unsigned long flags;

	eerb = (struct eerbuffer *) filp->private_data;
	spin_lock_irqsave(&bufferlock, flags);
	list_del(&eerb->list);
	spin_unlock_irqrestore(&bufferlock, flags);
	dasd_eer_free_buffer_pages(eerb->buffer, eerb->buffer_page_count);
	kfree(eerb->buffer);
	kfree(eerb);

	return 0;
}