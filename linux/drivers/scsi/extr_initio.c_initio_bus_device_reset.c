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
typedef  scalar_t__ u8 ;
struct target_control {int flags; } ;
struct scsi_ctrl_blk {scalar_t__ target; struct scsi_ctrl_blk* next; int /*<<< orphan*/  hastat; } ;
struct initio_host {scalar_t__ phase; scalar_t__ addr; struct scsi_ctrl_blk* last_busy; struct scsi_ctrl_blk* first_busy; struct target_control* active_tc; struct scsi_ctrl_blk* active; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_ABORTED ; 
 int /*<<< orphan*/  MSG_DEVRST ; 
 scalar_t__ MSG_OUT ; 
 int TCF_BUSY ; 
 int TCF_SYNC_DONE ; 
 int TCF_WDTR_DONE ; 
 int /*<<< orphan*/  TSC_XF_FIFO_OUT ; 
 scalar_t__ TUL_SCmd ; 
 scalar_t__ TUL_SFifo ; 
 int /*<<< orphan*/  initio_append_done_scb (struct initio_host*,struct scsi_ctrl_blk*) ; 
 int /*<<< orphan*/  initio_release_scb (struct initio_host*,struct scsi_ctrl_blk*) ; 
 int /*<<< orphan*/  initio_unlink_pend_scb (struct initio_host*,struct scsi_ctrl_blk*) ; 
 int initio_wait_disc (struct initio_host*) ; 
 int int_initio_bad_seq (struct initio_host*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

int initio_bus_device_reset(struct initio_host * host)
{
	struct scsi_ctrl_blk *scb = host->active;
	struct target_control *active_tc = host->active_tc;
	struct scsi_ctrl_blk *tmp, *prev;
	u8 tar;

	if (host->phase != MSG_OUT)
		return int_initio_bad_seq(host);	/* Unexpected phase */

	initio_unlink_pend_scb(host, scb);
	initio_release_scb(host, scb);


	tar = scb->target;	/* target                       */
	active_tc->flags &= ~(TCF_SYNC_DONE | TCF_WDTR_DONE | TCF_BUSY);
	/* clr sync. nego & WDTR flags  07/22/98 */

	/* abort all SCB with same target */
	prev = tmp = host->first_busy;	/* Check Busy queue */
	while (tmp != NULL) {
		if (tmp->target == tar) {
			/* unlink it */
			if (tmp == host->first_busy) {
				if ((host->first_busy = tmp->next) == NULL)
					host->last_busy = NULL;
			} else {
				prev->next = tmp->next;
				if (tmp == host->last_busy)
					host->last_busy = prev;
			}
			tmp->hastat = HOST_ABORTED;
			initio_append_done_scb(host, tmp);
		}
		/* Previous haven't change      */
		else {
			prev = tmp;
		}
		tmp = tmp->next;
	}
	outb(MSG_DEVRST, host->addr + TUL_SFifo);
	outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
	return initio_wait_disc(host);

}