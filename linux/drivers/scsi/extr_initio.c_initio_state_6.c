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
struct scsi_ctrl_blk {int next_state; } ;
struct initio_host {int phase; scalar_t__ addr; struct scsi_ctrl_blk* active; } ;

/* Variables and functions */
#define  DATA_IN 132 
#define  DATA_OUT 131 
#define  MSG_IN 130 
 int /*<<< orphan*/  MSG_NOP ; 
#define  MSG_OUT 129 
#define  STATUS_IN 128 
 int /*<<< orphan*/  TSC_XF_FIFO_OUT ; 
 scalar_t__ TUL_SCmd ; 
 scalar_t__ TUL_SFifo ; 
 int initio_bad_seq (struct initio_host*) ; 
 int initio_msgin (struct initio_host*) ; 
 int initio_status_msg (struct initio_host*) ; 
 int initio_xpad_in (struct initio_host*) ; 
 int initio_xpad_out (struct initio_host*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int wait_tulip (struct initio_host*) ; 

__attribute__((used)) static int initio_state_6(struct initio_host * host)
{
	struct scsi_ctrl_blk *scb = host->active;

#if DEBUG_STATE
	printk("-s6-");
#endif
	for (;;) {
		switch (host->phase) {
		case STATUS_IN:	/* Status phase                 */
			if ((initio_status_msg(host)) == -1)
				return -1;
			break;

		case MSG_IN:	/* Message in phase             */
			scb->next_state = 6;
			if ((initio_msgin(host)) == -1)
				return -1;
			break;

		case MSG_OUT:	/* Message out phase            */
			outb(MSG_NOP, host->addr + TUL_SFifo);		/* msg nop */
			outb(TSC_XF_FIFO_OUT, host->addr + TUL_SCmd);
			if (wait_tulip(host) == -1)
				return -1;
			break;

		case DATA_IN:	/* Data in phase                */
			return initio_xpad_in(host);

		case DATA_OUT:	/* Data out phase               */
			return initio_xpad_out(host);

		default:
			return initio_bad_seq(host);
		}
	}
}