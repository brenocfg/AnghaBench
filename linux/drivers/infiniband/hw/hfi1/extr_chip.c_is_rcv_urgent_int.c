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
struct hfi1_devdata {unsigned int num_rcv_contexts; } ;
struct hfi1_ctxtdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,char*,unsigned int) ; 
 int /*<<< orphan*/  handle_user_interrupt (struct hfi1_ctxtdata*) ; 
 struct hfi1_ctxtdata* hfi1_rcd_get_by_index (struct hfi1_devdata*,unsigned int) ; 
 int /*<<< orphan*/  hfi1_rcd_put (struct hfi1_ctxtdata*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static void is_rcv_urgent_int(struct hfi1_devdata *dd, unsigned int source)
{
	struct hfi1_ctxtdata *rcd;
	char *err_detail;

	if (likely(source < dd->num_rcv_contexts)) {
		rcd = hfi1_rcd_get_by_index(dd, source);
		if (rcd) {
			handle_user_interrupt(rcd);
			hfi1_rcd_put(rcd);
			return;	/* OK */
		}
		/* received an interrupt, but no rcd */
		err_detail = "dataless";
	} else {
		/* received an interrupt, but are not using that context */
		err_detail = "out of range";
	}
	dd_dev_err(dd, "unexpected %s receive urgent context interrupt %u\n",
		   err_detail, source);
}