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
struct hfi1_devdata {int num_rcv_contexts; } ;
struct hfi1_ctxtdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI1_RCVCTRL_CTXT_DIS ; 
 int /*<<< orphan*/  RCV_CTRL_RCV_PORT_ENABLE_SMASK ; 
 int /*<<< orphan*/  clear_rcvctrl (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 struct hfi1_ctxtdata* hfi1_rcd_get_by_index (struct hfi1_devdata*,int) ; 
 int /*<<< orphan*/  hfi1_rcd_put (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  hfi1_rcvctrl (struct hfi1_devdata*,int /*<<< orphan*/ ,struct hfi1_ctxtdata*) ; 

__attribute__((used)) static void rxe_freeze(struct hfi1_devdata *dd)
{
	int i;
	struct hfi1_ctxtdata *rcd;

	/* disable port */
	clear_rcvctrl(dd, RCV_CTRL_RCV_PORT_ENABLE_SMASK);

	/* disable all receive contexts */
	for (i = 0; i < dd->num_rcv_contexts; i++) {
		rcd = hfi1_rcd_get_by_index(dd, i);
		hfi1_rcvctrl(dd, HFI1_RCVCTRL_CTXT_DIS, rcd);
		hfi1_rcd_put(rcd);
	}
}