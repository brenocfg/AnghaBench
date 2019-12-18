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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct qib_pportdata {int lflags; int* statusp; int /*<<< orphan*/  lastibcstat; int /*<<< orphan*/  lflags_lock; int /*<<< orphan*/  symerr_clear_timer; struct qib_devdata* dd; } ;
struct qib_devdata {scalar_t__ (* f_iblink_state ) (int /*<<< orphan*/ ) ;scalar_t__ (* f_ibphys_portstate ) (int /*<<< orphan*/ ) ;int flags; int /*<<< orphan*/  (* f_setextled ) (struct qib_pportdata*,int) ;scalar_t__ (* f_ib_updown ) (struct qib_pportdata*,int,int /*<<< orphan*/ ) ;} ;
typedef  enum ib_event_type { ____Placeholder_ib_event_type } ib_event_type ;

/* Variables and functions */
 int IB_EVENT_PORT_ACTIVE ; 
 int IB_EVENT_PORT_ERR ; 
 scalar_t__ IB_PHYSPORTSTATE_CFG_TRAIN ; 
 scalar_t__ IB_PHYSPORTSTATE_LINKUP ; 
 scalar_t__ IB_PORT_ACTIVE ; 
 scalar_t__ IB_PORT_ARMED ; 
 scalar_t__ IB_PORT_DOWN ; 
 scalar_t__ IB_PORT_INIT ; 
 int QIBL_IB_FORCE_NOTIFY ; 
 int QIBL_LINKACTIVE ; 
 int QIBL_LINKARMED ; 
 int QIBL_LINKDOWN ; 
 int QIBL_LINKINIT ; 
 int QIBL_LINKV ; 
 int QIB_HAS_SEND_DMA ; 
 int QIB_STATUS_IB_CONF ; 
 int QIB_STATUS_IB_READY ; 
 int /*<<< orphan*/  _QIB_EVENT_LINKDOWN_BIT ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  qib_clear_symerror_on_linkup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_hol_up (struct qib_pportdata*) ; 
 int /*<<< orphan*/  qib_sdma_event_e30_go_running ; 
 int /*<<< orphan*/  qib_sdma_process_event (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_set_uevent_bits (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_ib_event (struct qib_pportdata*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (struct qib_pportdata*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stub4 (struct qib_pportdata*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct qib_pportdata*,int) ; 

void qib_handle_e_ibstatuschanged(struct qib_pportdata *ppd, u64 ibcs)
{
	struct qib_devdata *dd = ppd->dd;
	unsigned long flags;
	u32 lstate;
	u8 ltstate;
	enum ib_event_type ev = 0;

	lstate = dd->f_iblink_state(ibcs); /* linkstate */
	ltstate = dd->f_ibphys_portstate(ibcs);

	/*
	 * If linkstate transitions into INIT from any of the various down
	 * states, or if it transitions from any of the up (INIT or better)
	 * states into any of the down states (except link recovery), then
	 * call the chip-specific code to take appropriate actions.
	 *
	 * ppd->lflags could be 0 if this is the first time the interrupt
	 * handlers has been called but the link is already up.
	 */
	if (lstate >= IB_PORT_INIT &&
	    (!ppd->lflags || (ppd->lflags & QIBL_LINKDOWN)) &&
	    ltstate == IB_PHYSPORTSTATE_LINKUP) {
		/* transitioned to UP */
		if (dd->f_ib_updown(ppd, 1, ibcs))
			goto skip_ibchange; /* chip-code handled */
	} else if (ppd->lflags & (QIBL_LINKINIT | QIBL_LINKARMED |
		   QIBL_LINKACTIVE | QIBL_IB_FORCE_NOTIFY)) {
		if (ltstate != IB_PHYSPORTSTATE_LINKUP &&
		    ltstate <= IB_PHYSPORTSTATE_CFG_TRAIN &&
		    dd->f_ib_updown(ppd, 0, ibcs))
			goto skip_ibchange; /* chip-code handled */
		qib_set_uevent_bits(ppd, _QIB_EVENT_LINKDOWN_BIT);
	}

	if (lstate != IB_PORT_DOWN) {
		/* lstate is INIT, ARMED, or ACTIVE */
		if (lstate != IB_PORT_ACTIVE) {
			*ppd->statusp &= ~QIB_STATUS_IB_READY;
			if (ppd->lflags & QIBL_LINKACTIVE)
				ev = IB_EVENT_PORT_ERR;
			spin_lock_irqsave(&ppd->lflags_lock, flags);
			if (lstate == IB_PORT_ARMED) {
				ppd->lflags |= QIBL_LINKARMED | QIBL_LINKV;
				ppd->lflags &= ~(QIBL_LINKINIT |
					QIBL_LINKDOWN | QIBL_LINKACTIVE);
			} else {
				ppd->lflags |= QIBL_LINKINIT | QIBL_LINKV;
				ppd->lflags &= ~(QIBL_LINKARMED |
					QIBL_LINKDOWN | QIBL_LINKACTIVE);
			}
			spin_unlock_irqrestore(&ppd->lflags_lock, flags);
			/* start a 75msec timer to clear symbol errors */
			mod_timer(&ppd->symerr_clear_timer,
				  msecs_to_jiffies(75));
		} else if (ltstate == IB_PHYSPORTSTATE_LINKUP &&
			   !(ppd->lflags & QIBL_LINKACTIVE)) {
			/* active, but not active defered */
			qib_hol_up(ppd); /* useful only for 6120 now */
			*ppd->statusp |=
				QIB_STATUS_IB_READY | QIB_STATUS_IB_CONF;
			qib_clear_symerror_on_linkup(&ppd->symerr_clear_timer);
			spin_lock_irqsave(&ppd->lflags_lock, flags);
			ppd->lflags |= QIBL_LINKACTIVE | QIBL_LINKV;
			ppd->lflags &= ~(QIBL_LINKINIT |
				QIBL_LINKDOWN | QIBL_LINKARMED);
			spin_unlock_irqrestore(&ppd->lflags_lock, flags);
			if (dd->flags & QIB_HAS_SEND_DMA)
				qib_sdma_process_event(ppd,
					qib_sdma_event_e30_go_running);
			ev = IB_EVENT_PORT_ACTIVE;
			dd->f_setextled(ppd, 1);
		}
	} else { /* down */
		if (ppd->lflags & QIBL_LINKACTIVE)
			ev = IB_EVENT_PORT_ERR;
		spin_lock_irqsave(&ppd->lflags_lock, flags);
		ppd->lflags |= QIBL_LINKDOWN | QIBL_LINKV;
		ppd->lflags &= ~(QIBL_LINKINIT |
				 QIBL_LINKACTIVE | QIBL_LINKARMED);
		spin_unlock_irqrestore(&ppd->lflags_lock, flags);
		*ppd->statusp &= ~QIB_STATUS_IB_READY;
	}

skip_ibchange:
	ppd->lastibcstat = ibcs;
	if (ev)
		signal_ib_event(ppd, ev);
}