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
struct scsi_ctrl_blk {int /*<<< orphan*/  sglen; int /*<<< orphan*/  sgmax; scalar_t__ sgidx; scalar_t__ mode; } ;
struct initio_host {int semaph; int /*<<< orphan*/  semaph_lock; scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ TUL_Mask ; 
 int /*<<< orphan*/  initio_append_pend_scb (struct initio_host*,struct scsi_ctrl_blk*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tulip_main (struct initio_host*) ; 

__attribute__((used)) static void initio_exec_scb(struct initio_host * host, struct scsi_ctrl_blk * scb)
{
	unsigned long flags;

	scb->mode = 0;

	scb->sgidx = 0;
	scb->sgmax = scb->sglen;

	spin_lock_irqsave(&host->semaph_lock, flags);

	initio_append_pend_scb(host, scb);	/* Append this SCB to Pending queue */

/* VVVVV 07/21/98 */
	if (host->semaph == 1) {
		/* Disable Jasmin SCSI Int */
		outb(0x1F, host->addr + TUL_Mask);
		host->semaph = 0;
		spin_unlock_irqrestore(&host->semaph_lock, flags);

		tulip_main(host);

		spin_lock_irqsave(&host->semaph_lock, flags);
		host->semaph = 1;
		outb(0x0F, host->addr + TUL_Mask);
	}
	spin_unlock_irqrestore(&host->semaph_lock, flags);
	return;
}