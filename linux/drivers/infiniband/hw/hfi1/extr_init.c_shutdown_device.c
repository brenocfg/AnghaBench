#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hfi1_pportdata {int* statusp; int /*<<< orphan*/ * link_wq; int /*<<< orphan*/ * hfi1_wq; scalar_t__ linkup; } ;
struct hfi1_devdata {int flags; unsigned int num_pports; int num_rcv_contexts; int num_send_contexts; TYPE_1__* send_contexts; struct hfi1_pportdata* pport; } ;
struct hfi1_ctxtdata {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc; } ;

/* Variables and functions */
 int HFI1_INITTED ; 
 int HFI1_RCVCTRL_CTXT_DIS ; 
 int HFI1_RCVCTRL_INTRAVAIL_DIS ; 
 int HFI1_RCVCTRL_ONE_PKT_EGR_DIS ; 
 int HFI1_RCVCTRL_PKEY_DIS ; 
 int HFI1_RCVCTRL_TAILUPD_DIS ; 
 int HFI1_SHUTDOWN ; 
 int HFI1_STATUS_IB_CONF ; 
 int HFI1_STATUS_IB_READY ; 
 int /*<<< orphan*/  IS_FIRST_SOURCE ; 
 int /*<<< orphan*/  IS_LAST_SOURCE ; 
 int /*<<< orphan*/  PSC_GLOBAL_DISABLE ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfi1_quiet_serdes (struct hfi1_pportdata*) ; 
 struct hfi1_ctxtdata* hfi1_rcd_get_by_index (struct hfi1_devdata*,int) ; 
 int /*<<< orphan*/  hfi1_rcd_put (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  hfi1_rcvctrl (struct hfi1_devdata*,int,struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  msix_clean_up_interrupts (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  pio_send_control (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_exit (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  set_intr_bits (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  shutdown_led_override (struct hfi1_pportdata*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void shutdown_device(struct hfi1_devdata *dd)
{
	struct hfi1_pportdata *ppd;
	struct hfi1_ctxtdata *rcd;
	unsigned pidx;
	int i;

	if (dd->flags & HFI1_SHUTDOWN)
		return;
	dd->flags |= HFI1_SHUTDOWN;

	for (pidx = 0; pidx < dd->num_pports; ++pidx) {
		ppd = dd->pport + pidx;

		ppd->linkup = 0;
		if (ppd->statusp)
			*ppd->statusp &= ~(HFI1_STATUS_IB_CONF |
					   HFI1_STATUS_IB_READY);
	}
	dd->flags &= ~HFI1_INITTED;

	/* mask and clean up interrupts */
	set_intr_bits(dd, IS_FIRST_SOURCE, IS_LAST_SOURCE, false);
	msix_clean_up_interrupts(dd);

	for (pidx = 0; pidx < dd->num_pports; ++pidx) {
		ppd = dd->pport + pidx;
		for (i = 0; i < dd->num_rcv_contexts; i++) {
			rcd = hfi1_rcd_get_by_index(dd, i);
			hfi1_rcvctrl(dd, HFI1_RCVCTRL_TAILUPD_DIS |
				     HFI1_RCVCTRL_CTXT_DIS |
				     HFI1_RCVCTRL_INTRAVAIL_DIS |
				     HFI1_RCVCTRL_PKEY_DIS |
				     HFI1_RCVCTRL_ONE_PKT_EGR_DIS, rcd);
			hfi1_rcd_put(rcd);
		}
		/*
		 * Gracefully stop all sends allowing any in progress to
		 * trickle out first.
		 */
		for (i = 0; i < dd->num_send_contexts; i++)
			sc_flush(dd->send_contexts[i].sc);
	}

	/*
	 * Enough for anything that's going to trickle out to have actually
	 * done so.
	 */
	udelay(20);

	for (pidx = 0; pidx < dd->num_pports; ++pidx) {
		ppd = dd->pport + pidx;

		/* disable all contexts */
		for (i = 0; i < dd->num_send_contexts; i++)
			sc_disable(dd->send_contexts[i].sc);
		/* disable the send device */
		pio_send_control(dd, PSC_GLOBAL_DISABLE);

		shutdown_led_override(ppd);

		/*
		 * Clear SerdesEnable.
		 * We can't count on interrupts since we are stopping.
		 */
		hfi1_quiet_serdes(ppd);

		if (ppd->hfi1_wq) {
			destroy_workqueue(ppd->hfi1_wq);
			ppd->hfi1_wq = NULL;
		}
		if (ppd->link_wq) {
			destroy_workqueue(ppd->link_wq);
			ppd->link_wq = NULL;
		}
	}
	sdma_exit(dd);
}