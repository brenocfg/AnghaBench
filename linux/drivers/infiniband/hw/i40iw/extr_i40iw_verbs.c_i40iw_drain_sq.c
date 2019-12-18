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
struct ib_qp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sq_ring; } ;
struct i40iw_sc_qp {TYPE_1__ qp_uk; } ;
struct i40iw_qp {int /*<<< orphan*/  sq_drained; struct i40iw_sc_qp sc_qp; } ;

/* Variables and functions */
 scalar_t__ I40IW_RING_MORE_WORK (int /*<<< orphan*/ ) ; 
 struct i40iw_qp* to_iwqp (struct ib_qp*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i40iw_drain_sq(struct ib_qp *ibqp)
{
	struct i40iw_qp *iwqp = to_iwqp(ibqp);
	struct i40iw_sc_qp *qp = &iwqp->sc_qp;

	if (I40IW_RING_MORE_WORK(qp->qp_uk.sq_ring))
		wait_for_completion(&iwqp->sq_drained);
}