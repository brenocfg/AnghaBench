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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct hfi1_devdata {scalar_t__ first_dyn_alloc_ctxt; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/  sc; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RTAIL ; 
 scalar_t__ HFI1_CAP_IS_KSET (int /*<<< orphan*/ ) ; 
 scalar_t__ HFI1_CAP_KGET_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HFI1_RCVCTRL_CTXT_ENB ; 
 int HFI1_RCVCTRL_INTRAVAIL_ENB ; 
 int HFI1_RCVCTRL_NO_EGR_DROP_ENB ; 
 int HFI1_RCVCTRL_NO_RHQ_DROP_ENB ; 
 int HFI1_RCVCTRL_ONE_PKT_EGR_ENB ; 
 int HFI1_RCVCTRL_TAILUPD_DIS ; 
 int HFI1_RCVCTRL_TAILUPD_ENB ; 
 int HFI1_RCVCTRL_TIDFLOW_ENB ; 
 int /*<<< orphan*/  MULTI_PKT_EGR ; 
 int /*<<< orphan*/  NODROP_EGR_FULL ; 
 int /*<<< orphan*/  NODROP_RHQ_FULL ; 
 int /*<<< orphan*/  PSC_GLOBAL_ENABLE ; 
 int /*<<< orphan*/  TID_RDMA ; 
 struct hfi1_ctxtdata* hfi1_rcd_get_by_index (struct hfi1_devdata*,scalar_t__) ; 
 int /*<<< orphan*/  hfi1_rcd_put (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  hfi1_rcvctrl (struct hfi1_devdata*,int,struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  pio_send_control (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_chip(struct hfi1_devdata *dd)
{
	struct hfi1_ctxtdata *rcd;
	u32 rcvmask;
	u16 i;

	/* enable PIO send */
	pio_send_control(dd, PSC_GLOBAL_ENABLE);

	/*
	 * Enable kernel ctxts' receive and receive interrupt.
	 * Other ctxts done as user opens and initializes them.
	 */
	for (i = 0; i < dd->first_dyn_alloc_ctxt; ++i) {
		rcd = hfi1_rcd_get_by_index(dd, i);
		if (!rcd)
			continue;
		rcvmask = HFI1_RCVCTRL_CTXT_ENB | HFI1_RCVCTRL_INTRAVAIL_ENB;
		rcvmask |= HFI1_CAP_KGET_MASK(rcd->flags, DMA_RTAIL) ?
			HFI1_RCVCTRL_TAILUPD_ENB : HFI1_RCVCTRL_TAILUPD_DIS;
		if (!HFI1_CAP_KGET_MASK(rcd->flags, MULTI_PKT_EGR))
			rcvmask |= HFI1_RCVCTRL_ONE_PKT_EGR_ENB;
		if (HFI1_CAP_KGET_MASK(rcd->flags, NODROP_RHQ_FULL))
			rcvmask |= HFI1_RCVCTRL_NO_RHQ_DROP_ENB;
		if (HFI1_CAP_KGET_MASK(rcd->flags, NODROP_EGR_FULL))
			rcvmask |= HFI1_RCVCTRL_NO_EGR_DROP_ENB;
		if (HFI1_CAP_IS_KSET(TID_RDMA))
			rcvmask |= HFI1_RCVCTRL_TIDFLOW_ENB;
		hfi1_rcvctrl(dd, rcvmask, rcd);
		sc_enable(rcd->sc);
		hfi1_rcd_put(rcd);
	}
}