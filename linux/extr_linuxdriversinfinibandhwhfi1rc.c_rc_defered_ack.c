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
struct rvt_qp {int /*<<< orphan*/  rspwait; int /*<<< orphan*/  r_flags; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/  qp_wait_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  RVT_R_RSP_NAK ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_get_qp (struct rvt_qp*) ; 

__attribute__((used)) static inline void rc_defered_ack(struct hfi1_ctxtdata *rcd,
				  struct rvt_qp *qp)
{
	if (list_empty(&qp->rspwait)) {
		qp->r_flags |= RVT_R_RSP_NAK;
		rvt_get_qp(qp);
		list_add_tail(&qp->rspwait, &rcd->qp_wait_list);
	}
}