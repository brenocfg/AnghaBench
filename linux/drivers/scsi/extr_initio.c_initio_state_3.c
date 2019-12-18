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
struct target_control {int flags; } ;
struct scsi_ctrl_blk {int* cdb; int next_state; scalar_t__ cdblen; } ;
struct initio_host {int phase; scalar_t__ addr; struct target_control* active_tc; struct scsi_ctrl_blk* active; } ;

/* Variables and functions */
#define  CMD_OUT 131 
 int MAX_OFFSET ; 
 int MSG_EXTEND ; 
#define  MSG_IN 130 
 int MSG_NOP ; 
#define  MSG_OUT 129 
#define  STATUS_IN 128 
 int TCF_NO_SYNC_NEGO ; 
 size_t TCF_SCSI_RATE ; 
 int TCF_SYNC_DONE ; 
 int TSC_FLUSH_FIFO ; 
 int TSC_SET_ACK ; 
 int TSC_XF_FIFO_OUT ; 
 scalar_t__ TUL_SCmd ; 
 scalar_t__ TUL_SCtrl0 ; 
 scalar_t__ TUL_SFifo ; 
 scalar_t__ TUL_SSignal ; 
 int inb (scalar_t__) ; 
 int initio_bad_seq (struct initio_host*) ; 
 int initio_msgin (struct initio_host*) ; 
 int* initio_rate_tbl ; 
 int initio_status_msg (struct initio_host*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int wait_tulip (struct initio_host*) ; 

__attribute__((used)) static int initio_state_3(struct initio_host * host)
{
	struct scsi_ctrl_blk *scb = host->active;
	struct target_control *active_tc = host->active_tc;
	int i;

#if DEBUG_STATE
	printk("-s3-");
#endif
	for (;;) {
		switch (host->phase) {
		case CMD_OUT:	/* Command out phase            */
			for (i = 0; i < (int) scb->cdblen; i++)
				outb(scb->cdb[i], host->addr + TUL_SFifo);
			outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
			if (wait_tulip(host) == -1)
				return -1;
			if (host->phase == CMD_OUT)
				return initio_bad_seq(host);
			return 4;

		case MSG_IN:	/* Message in phase             */
			scb->next_state = 3;
			if (initio_msgin(host) == -1)
				return -1;
			break;

		case STATUS_IN:	/* Status phase                 */
			if (initio_status_msg(host) == -1)
				return -1;
			break;

		case MSG_OUT:	/* Message out phase            */
			if (active_tc->flags & (TCF_SYNC_DONE | TCF_NO_SYNC_NEGO)) {
				outb(MSG_NOP, host->addr + TUL_SFifo);		/* msg nop */
				outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
				if (wait_tulip(host) == -1)
					return -1;
			} else {
				active_tc->flags |= TCF_SYNC_DONE;

				outb(MSG_EXTEND, host->addr + TUL_SFifo);
				outb(3, host->addr + TUL_SFifo);	/* ext. msg len */
				outb(1, host->addr + TUL_SFifo);	/* sync request */
				outb(initio_rate_tbl[active_tc->flags & TCF_SCSI_RATE], host->addr + TUL_SFifo);
				outb(MAX_OFFSET, host->addr + TUL_SFifo);	/* REQ/ACK offset */
				outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
				if (wait_tulip(host) == -1)
					return -1;
				outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);
				outb(inb(host->addr + TUL_SSignal) & (TSC_SET_ACK | 7), host->addr + TUL_SSignal);

			}
			break;
		default:
			return initio_bad_seq(host);
		}
	}
}