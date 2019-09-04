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
struct qib_devdata {int ctxtcnt; int first_user_ctxt; int num_pports; int qpn_mask; int n_krcv_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  kr_portcnt ; 
 int qib_n_krcv_queues ; 
 int qib_read_kreg32 (struct qib_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qib_6120_config_ctxts(struct qib_devdata *dd)
{
	dd->ctxtcnt = qib_read_kreg32(dd, kr_portcnt);
	if (qib_n_krcv_queues > 1) {
		dd->first_user_ctxt = qib_n_krcv_queues * dd->num_pports;
		if (dd->first_user_ctxt > dd->ctxtcnt)
			dd->first_user_ctxt = dd->ctxtcnt;
		dd->qpn_mask = dd->first_user_ctxt <= 2 ? 2 : 6;
	} else
		dd->first_user_ctxt = dd->num_pports;
	dd->n_krcv_queues = dd->first_user_ctxt;
}