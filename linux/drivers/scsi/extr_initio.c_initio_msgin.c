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
struct initio_host {scalar_t__ phase; scalar_t__ addr; struct target_control* active_tc; } ;

/* Variables and functions */
#define  MSG_COMP 135 
#define  MSG_DISC 134 
#define  MSG_EXTEND 133 
#define  MSG_IGNOREWIDE 132 
 scalar_t__ MSG_IN ; 
#define  MSG_NOP 131 
#define  MSG_REJ 130 
#define  MSG_RESTORE 129 
#define  MSG_SDP 128 
 int TCF_NO_SYNC_NEGO ; 
 int TCF_SYNC_DONE ; 
 int TSC_FLUSH_FIFO ; 
 int TSC_MSG_ACCEPT ; 
 int TSC_SET_ACK ; 
 int TSC_SET_ATN ; 
 int TSC_XF_FIFO_IN ; 
 scalar_t__ TUL_SCmd ; 
 scalar_t__ TUL_SCnt0 ; 
 scalar_t__ TUL_SCtrl0 ; 
 scalar_t__ TUL_SFifo ; 
 scalar_t__ TUL_SSignal ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  initio_msgin_accept (struct initio_host*) ; 
 int /*<<< orphan*/  initio_msgin_extend (struct initio_host*) ; 
 int /*<<< orphan*/  initio_msgout_reject (struct initio_host*) ; 
 int initio_wait_disc (struct initio_host*) ; 
 int initio_wait_done_disc (struct initio_host*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int wait_tulip (struct initio_host*) ; 

__attribute__((used)) static int initio_msgin(struct initio_host * host)
{
	struct target_control *active_tc;

	for (;;) {
		outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);

		outl(1, host->addr + TUL_SCnt0);
		outb(TSC_XF_FIFO_IN, host->addr + TUL_SCmd);
		if (wait_tulip(host) == -1)
			return -1;

		switch (inb(host->addr + TUL_SFifo)) {
		case MSG_DISC:	/* Disconnect msg */
			outb(TSC_MSG_ACCEPT, host->addr + TUL_SCmd);
			return initio_wait_disc(host);
		case MSG_SDP:
		case MSG_RESTORE:
		case MSG_NOP:
			initio_msgin_accept(host);
			break;
		case MSG_REJ:	/* Clear ATN first              */
			outb((inb(host->addr + TUL_SSignal) & (TSC_SET_ACK | 7)),
				host->addr + TUL_SSignal);
			active_tc = host->active_tc;
			if ((active_tc->flags & (TCF_SYNC_DONE | TCF_NO_SYNC_NEGO)) == 0)	/* do sync nego */
				outb(((inb(host->addr + TUL_SSignal) & (TSC_SET_ACK | 7)) | TSC_SET_ATN),
					host->addr + TUL_SSignal);
			initio_msgin_accept(host);
			break;
		case MSG_EXTEND:	/* extended msg */
			initio_msgin_extend(host);
			break;
		case MSG_IGNOREWIDE:
			initio_msgin_accept(host);
			break;
		case MSG_COMP:
			outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);
			outb(TSC_MSG_ACCEPT, host->addr + TUL_SCmd);
			return initio_wait_done_disc(host);
		default:
			initio_msgout_reject(host);
			break;
		}
		if (host->phase != MSG_IN)
			return host->phase;
	}
	/* statement won't reach here */
}