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
struct TYPE_2__ {scalar_t__ qp_type; } ;
struct rvt_qp {TYPE_1__ ibqp; scalar_t__ r_adefered; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_RC ; 
 int /*<<< orphan*/  clear_ahg (struct rvt_qp*) ; 
 int /*<<< orphan*/  hfi1_qp_kern_exp_rcv_clear_all (struct rvt_qp*) ; 
 int /*<<< orphan*/  opfn_conn_error (struct rvt_qp*) ; 

void notify_qp_reset(struct rvt_qp *qp)
{
	hfi1_qp_kern_exp_rcv_clear_all(qp);
	qp->r_adefered = 0;
	clear_ahg(qp);

	/* Clear any OPFN state */
	if (qp->ibqp.qp_type == IB_QPT_RC)
		opfn_conn_error(qp);
}