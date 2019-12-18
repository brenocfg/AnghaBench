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
struct scsi_ctrl_blk {int /*<<< orphan*/  status; struct scsi_ctrl_blk* next; } ;
struct initio_host {int /*<<< orphan*/  avail_lock; int /*<<< orphan*/ * last_avail; struct scsi_ctrl_blk* first_avail; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCB_RENT ; 
 int /*<<< orphan*/  printk (char*,struct scsi_ctrl_blk*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct scsi_ctrl_blk *initio_alloc_scb(struct initio_host *host)
{
	struct scsi_ctrl_blk *scb;
	unsigned long flags;

	spin_lock_irqsave(&host->avail_lock, flags);
	if ((scb = host->first_avail) != NULL) {
#if DEBUG_QUEUE
		printk("find scb at %p\n", scb);
#endif
		if ((host->first_avail = scb->next) == NULL)
			host->last_avail = NULL;
		scb->next = NULL;
		scb->status = SCB_RENT;
	}
	spin_unlock_irqrestore(&host->avail_lock, flags);
	return scb;
}