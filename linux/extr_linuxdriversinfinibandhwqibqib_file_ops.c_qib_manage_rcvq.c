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
struct qib_devdata {int /*<<< orphan*/  (* f_rcvctrl ) (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ;} ;
struct qib_ctxtdata {int /*<<< orphan*/  ctxt; int /*<<< orphan*/  ppd; scalar_t__ rcvhdrtail_kvaddr; struct qib_devdata* dd; } ;

/* Variables and functions */
 unsigned int QIB_RCVCTRL_CTXT_DIS ; 
 unsigned int QIB_RCVCTRL_CTXT_ENB ; 
 int /*<<< orphan*/  qib_clear_rcvhdrtail (struct qib_ctxtdata*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qib_manage_rcvq(struct qib_ctxtdata *rcd, unsigned subctxt,
			   int start_stop)
{
	struct qib_devdata *dd = rcd->dd;
	unsigned int rcvctrl_op;

	if (subctxt)
		goto bail;
	/* atomically clear receive enable ctxt. */
	if (start_stop) {
		/*
		 * On enable, force in-memory copy of the tail register to
		 * 0, so that protocol code doesn't have to worry about
		 * whether or not the chip has yet updated the in-memory
		 * copy or not on return from the system call. The chip
		 * always resets it's tail register back to 0 on a
		 * transition from disabled to enabled.
		 */
		if (rcd->rcvhdrtail_kvaddr)
			qib_clear_rcvhdrtail(rcd);
		rcvctrl_op = QIB_RCVCTRL_CTXT_ENB;
	} else
		rcvctrl_op = QIB_RCVCTRL_CTXT_DIS;
	dd->f_rcvctrl(rcd->ppd, rcvctrl_op, rcd->ctxt);
	/* always; new head should be equal to new tail; see above */
bail:
	return 0;
}