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
typedef  int u64 ;
struct qib_devdata {int num_pports; int flags; int first_user_ctxt; int /*<<< orphan*/  (* f_rcvctrl ) (int /*<<< orphan*/ ,int,int) ;struct qib_ctxtdata** rcd; scalar_t__ pport; int /*<<< orphan*/  (* f_sendctrl ) (scalar_t__,int) ;} ;
struct qib_ctxtdata {int /*<<< orphan*/  ppd; } ;

/* Variables and functions */
 int QIB_NODMA_RTAIL ; 
 int QIB_RCVCTRL_CTXT_ENB ; 
 int QIB_RCVCTRL_INTRAVAIL_ENB ; 
 int QIB_RCVCTRL_TAILUPD_DIS ; 
 int QIB_RCVCTRL_TAILUPD_ENB ; 
 int QIB_SENDCTRL_AVAIL_ENB ; 
 int QIB_SENDCTRL_SEND_ENB ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void enable_chip(struct qib_devdata *dd)
{
	u64 rcvmask;
	int i;

	/*
	 * Enable PIO send, and update of PIOavail regs to memory.
	 */
	for (i = 0; i < dd->num_pports; ++i)
		dd->f_sendctrl(dd->pport + i, QIB_SENDCTRL_SEND_ENB |
			QIB_SENDCTRL_AVAIL_ENB);
	/*
	 * Enable kernel ctxts' receive and receive interrupt.
	 * Other ctxts done as user opens and inits them.
	 */
	rcvmask = QIB_RCVCTRL_CTXT_ENB | QIB_RCVCTRL_INTRAVAIL_ENB;
	rcvmask |= (dd->flags & QIB_NODMA_RTAIL) ?
		  QIB_RCVCTRL_TAILUPD_DIS : QIB_RCVCTRL_TAILUPD_ENB;
	for (i = 0; dd->rcd && i < dd->first_user_ctxt; ++i) {
		struct qib_ctxtdata *rcd = dd->rcd[i];

		if (rcd)
			dd->f_rcvctrl(rcd->ppd, rcvmask, i);
	}
}