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
struct target_control {int sconfig0; int flags; } ;
struct scsi_ctrl_blk {int ident; int tagmsg; int tagid; } ;
struct initio_host {scalar_t__ phase; scalar_t__ addr; struct target_control* active_tc; struct scsi_ctrl_blk* active; } ;

/* Variables and functions */
 int MAX_OFFSET ; 
 int MSG_EXTEND ; 
 scalar_t__ MSG_OUT ; 
 int TCF_NO_SYNC_NEGO ; 
 int TCF_NO_WDTR ; 
 size_t TCF_SCSI_RATE ; 
 int TCF_SYNC_DONE ; 
 int TCF_WDTR_DONE ; 
 int TSC_EN_BUS_IN ; 
 int TSC_FLUSH_FIFO ; 
 int TSC_HW_RESELECT ; 
 int TSC_SET_ACK ; 
 int TSC_XF_FIFO_OUT ; 
 scalar_t__ TUL_SCmd ; 
 scalar_t__ TUL_SConfig ; 
 scalar_t__ TUL_SCtrl0 ; 
 scalar_t__ TUL_SCtrl1 ; 
 scalar_t__ TUL_SFifo ; 
 scalar_t__ TUL_SSignal ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  initio_append_busy_scb (struct initio_host*,struct scsi_ctrl_blk*) ; 
 int* initio_rate_tbl ; 
 int /*<<< orphan*/  initio_unlink_pend_scb (struct initio_host*,struct scsi_ctrl_blk*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int wait_tulip (struct initio_host*) ; 

__attribute__((used)) static int initio_state_1(struct initio_host * host)
{
	struct scsi_ctrl_blk *scb = host->active;
	struct target_control *active_tc = host->active_tc;
#if DEBUG_STATE
	printk("-s1-");
#endif

	/* Move the SCB from pending to busy */
	initio_unlink_pend_scb(host, scb);
	initio_append_busy_scb(host, scb);

	outb(active_tc->sconfig0, host->addr + TUL_SConfig );
	/* ATN on */
	if (host->phase == MSG_OUT) {
		outb(TSC_EN_BUS_IN | TSC_HW_RESELECT, host->addr + TUL_SCtrl1);
		outb(scb->ident, host->addr + TUL_SFifo);

		if (scb->tagmsg) {
			outb(scb->tagmsg, host->addr + TUL_SFifo);
			outb(scb->tagid, host->addr + TUL_SFifo);
		}
		if ((active_tc->flags & (TCF_WDTR_DONE | TCF_NO_WDTR)) == 0) {
			active_tc->flags |= TCF_WDTR_DONE;
			outb(MSG_EXTEND, host->addr + TUL_SFifo);
			outb(2, host->addr + TUL_SFifo);	/* Extended msg length */
			outb(3, host->addr + TUL_SFifo);	/* Sync request */
			outb(1, host->addr + TUL_SFifo);	/* Start from 16 bits */
		} else if ((active_tc->flags & (TCF_SYNC_DONE | TCF_NO_SYNC_NEGO)) == 0) {
			active_tc->flags |= TCF_SYNC_DONE;
			outb(MSG_EXTEND, host->addr + TUL_SFifo);
			outb(3, host->addr + TUL_SFifo);	/* extended msg length */
			outb(1, host->addr + TUL_SFifo);	/* sync request */
			outb(initio_rate_tbl[active_tc->flags & TCF_SCSI_RATE], host->addr + TUL_SFifo);
			outb(MAX_OFFSET, host->addr + TUL_SFifo);	/* REQ/ACK offset */
		}
		outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
		if (wait_tulip(host) == -1)
			return -1;
	}
	outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);
	outb((inb(host->addr + TUL_SSignal) & (TSC_SET_ACK | 7)), host->addr + TUL_SSignal);
	/* Into before CDB xfer */
	return 3;
}