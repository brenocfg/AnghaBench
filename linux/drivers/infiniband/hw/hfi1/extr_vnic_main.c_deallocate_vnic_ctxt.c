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
struct hfi1_devdata {int dummy; } ;
struct hfi1_ctxtdata {scalar_t__ event_flags; scalar_t__ msix_intr; int /*<<< orphan*/  ctxt; } ;
struct TYPE_2__ {int /*<<< orphan*/  sps_ctxts; } ;

/* Variables and functions */
 int HFI1_RCVCTRL_CTXT_DIS ; 
 int HFI1_RCVCTRL_INTRAVAIL_DIS ; 
 int HFI1_RCVCTRL_NO_EGR_DROP_DIS ; 
 int HFI1_RCVCTRL_NO_RHQ_DROP_DIS ; 
 int HFI1_RCVCTRL_ONE_PKT_EGR_DIS ; 
 int HFI1_RCVCTRL_TIDFLOW_DIS ; 
 int /*<<< orphan*/  dd_dev_dbg (struct hfi1_devdata*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_wc () ; 
 int /*<<< orphan*/  hfi1_clear_ctxt_pkey (struct hfi1_devdata*,struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  hfi1_clear_tids (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  hfi1_free_ctxt (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  hfi1_rcvctrl (struct hfi1_devdata*,int,struct hfi1_ctxtdata*) ; 
 TYPE_1__ hfi1_stats ; 
 int /*<<< orphan*/  msix_free_irq (struct hfi1_devdata*,scalar_t__) ; 

__attribute__((used)) static void deallocate_vnic_ctxt(struct hfi1_devdata *dd,
				 struct hfi1_ctxtdata *uctxt)
{
	dd_dev_dbg(dd, "closing vnic context %d\n", uctxt->ctxt);
	flush_wc();

	/*
	 * Disable receive context and interrupt available, reset all
	 * RcvCtxtCtrl bits to default values.
	 */
	hfi1_rcvctrl(dd, HFI1_RCVCTRL_CTXT_DIS |
		     HFI1_RCVCTRL_TIDFLOW_DIS |
		     HFI1_RCVCTRL_INTRAVAIL_DIS |
		     HFI1_RCVCTRL_ONE_PKT_EGR_DIS |
		     HFI1_RCVCTRL_NO_RHQ_DROP_DIS |
		     HFI1_RCVCTRL_NO_EGR_DROP_DIS, uctxt);

	/* msix_intr will always be > 0, only clean up if this is true */
	if (uctxt->msix_intr)
		msix_free_irq(dd, uctxt->msix_intr);

	uctxt->event_flags = 0;

	hfi1_clear_tids(uctxt);
	hfi1_clear_ctxt_pkey(dd, uctxt);

	hfi1_stats.sps_ctxts--;

	hfi1_free_ctxt(uctxt);
}