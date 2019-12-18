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
typedef  scalar_t__ u16 ;
struct hfi1_devdata {scalar_t__ num_rcv_contexts; scalar_t__ first_dyn_alloc_ctxt; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/ * do_interrupt; scalar_t__ is_vnic; } ;

/* Variables and functions */
 scalar_t__ HFI1_CTRL_CTXT ; 
 int /*<<< orphan*/  handle_receive_interrupt ; 
 struct hfi1_ctxtdata* hfi1_rcd_get_by_index (struct hfi1_devdata*,scalar_t__) ; 
 int /*<<< orphan*/  hfi1_rcd_put (struct hfi1_ctxtdata*) ; 

void set_all_slowpath(struct hfi1_devdata *dd)
{
	struct hfi1_ctxtdata *rcd;
	u16 i;

	/* HFI1_CTRL_CTXT must always use the slow path interrupt handler */
	for (i = HFI1_CTRL_CTXT + 1; i < dd->num_rcv_contexts; i++) {
		rcd = hfi1_rcd_get_by_index(dd, i);
		if (!rcd)
			continue;
		if (i < dd->first_dyn_alloc_ctxt || rcd->is_vnic)
			rcd->do_interrupt = &handle_receive_interrupt;

		hfi1_rcd_put(rcd);
	}
}