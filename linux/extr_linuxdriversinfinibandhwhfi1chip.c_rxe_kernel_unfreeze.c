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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct hfi1_devdata {scalar_t__ num_rcv_contexts; scalar_t__ first_dyn_alloc_ctxt; } ;
struct hfi1_ctxtdata {scalar_t__ rcvhdrtail_kvaddr; int /*<<< orphan*/  is_vnic; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI1_RCVCTRL_CTXT_ENB ; 
 int /*<<< orphan*/  HFI1_RCVCTRL_TAILUPD_DIS ; 
 int /*<<< orphan*/  HFI1_RCVCTRL_TAILUPD_ENB ; 
 int /*<<< orphan*/  RCV_CTRL_RCV_PORT_ENABLE_SMASK ; 
 int /*<<< orphan*/  add_rcvctrl (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 struct hfi1_ctxtdata* hfi1_rcd_get_by_index (struct hfi1_devdata*,scalar_t__) ; 
 int /*<<< orphan*/  hfi1_rcd_put (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  hfi1_rcvctrl (struct hfi1_devdata*,int /*<<< orphan*/ ,struct hfi1_ctxtdata*) ; 

__attribute__((used)) static void rxe_kernel_unfreeze(struct hfi1_devdata *dd)
{
	u32 rcvmask;
	u16 i;
	struct hfi1_ctxtdata *rcd;

	/* enable all kernel contexts */
	for (i = 0; i < dd->num_rcv_contexts; i++) {
		rcd = hfi1_rcd_get_by_index(dd, i);

		/* Ensure all non-user contexts(including vnic) are enabled */
		if (!rcd ||
		    (i >= dd->first_dyn_alloc_ctxt && !rcd->is_vnic)) {
			hfi1_rcd_put(rcd);
			continue;
		}
		rcvmask = HFI1_RCVCTRL_CTXT_ENB;
		/* HFI1_RCVCTRL_TAILUPD_[ENB|DIS] needs to be set explicitly */
		rcvmask |= rcd->rcvhdrtail_kvaddr ?
			HFI1_RCVCTRL_TAILUPD_ENB : HFI1_RCVCTRL_TAILUPD_DIS;
		hfi1_rcvctrl(dd, rcvmask, rcd);
		hfi1_rcd_put(rcd);
	}

	/* enable port */
	add_rcvctrl(dd, RCV_CTRL_RCV_PORT_ENABLE_SMASK);
}