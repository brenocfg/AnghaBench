#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_4__ {int current_state; } ;
struct qib_pportdata {int /*<<< orphan*/  sdma_lock; TYPE_2__ sdma_state; int /*<<< orphan*/  port; struct qib_devdata* dd; } ;
struct qib_devdata {int /*<<< orphan*/  unit; TYPE_1__* cspec; } ;
struct TYPE_3__ {char* sdmamsgbuf; } ;

/* Variables and functions */
 int DISABLES_SDMA ; 
 int ERR_MASK (int /*<<< orphan*/ ) ; 
 int QLOGIC_IB_E_SDMAERRS ; 
 int /*<<< orphan*/  SDmaDisabledErr ; 
 int /*<<< orphan*/  SDmaUnexpDataErr ; 
 int /*<<< orphan*/  SendBufMisuseErr ; 
 int /*<<< orphan*/  __qib_sdma_process_event (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ kr_sendbuffererror ; 
 int /*<<< orphan*/  qib_decode_7220_sdma_errs (struct qib_pportdata*,int,char*,int) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 unsigned long qib_read_kreg64 (struct qib_devdata*,scalar_t__) ; 
 int /*<<< orphan*/  qib_sdma_event_e50_hw_cleaned ; 
 int /*<<< orphan*/  qib_sdma_event_e7220_err_halted ; 
#define  qib_sdma_state_s00_hw_down 134 
#define  qib_sdma_state_s10_hw_start_up_wait 133 
#define  qib_sdma_state_s20_idle 132 
#define  qib_sdma_state_s30_sw_clean_up_wait 131 
#define  qib_sdma_state_s40_hw_clean_up_wait 130 
#define  qib_sdma_state_s50_hw_halt_wait 129 
#define  qib_sdma_state_s99_running 128 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sdma_7220_errors(struct qib_pportdata *ppd, u64 errs)
{
	unsigned long flags;
	struct qib_devdata *dd = ppd->dd;
	char *msg;

	errs &= QLOGIC_IB_E_SDMAERRS;

	msg = dd->cspec->sdmamsgbuf;
	qib_decode_7220_sdma_errs(ppd, errs, msg,
		sizeof(dd->cspec->sdmamsgbuf));
	spin_lock_irqsave(&ppd->sdma_lock, flags);

	if (errs & ERR_MASK(SendBufMisuseErr)) {
		unsigned long sbuf[3];

		sbuf[0] = qib_read_kreg64(dd, kr_sendbuffererror);
		sbuf[1] = qib_read_kreg64(dd, kr_sendbuffererror + 1);
		sbuf[2] = qib_read_kreg64(dd, kr_sendbuffererror + 2);

		qib_dev_err(ppd->dd,
			    "IB%u:%u SendBufMisuse: %04lx %016lx %016lx\n",
			    ppd->dd->unit, ppd->port, sbuf[2], sbuf[1],
			    sbuf[0]);
	}

	if (errs & ERR_MASK(SDmaUnexpDataErr))
		qib_dev_err(dd, "IB%u:%u SDmaUnexpData\n", ppd->dd->unit,
			    ppd->port);

	switch (ppd->sdma_state.current_state) {
	case qib_sdma_state_s00_hw_down:
		/* not expecting any interrupts */
		break;

	case qib_sdma_state_s10_hw_start_up_wait:
		/* handled in intr path */
		break;

	case qib_sdma_state_s20_idle:
		/* not expecting any interrupts */
		break;

	case qib_sdma_state_s30_sw_clean_up_wait:
		/* not expecting any interrupts */
		break;

	case qib_sdma_state_s40_hw_clean_up_wait:
		if (errs & ERR_MASK(SDmaDisabledErr))
			__qib_sdma_process_event(ppd,
				qib_sdma_event_e50_hw_cleaned);
		break;

	case qib_sdma_state_s50_hw_halt_wait:
		/* handled in intr path */
		break;

	case qib_sdma_state_s99_running:
		if (errs & DISABLES_SDMA)
			__qib_sdma_process_event(ppd,
				qib_sdma_event_e7220_err_halted);
		break;
	}

	spin_unlock_irqrestore(&ppd->sdma_lock, flags);
}