#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct rxe_qp {int mtu; TYPE_1__ ibqp; } ;
struct TYPE_4__ {int mtu_cap; } ;
struct rxe_dev {TYPE_2__ port; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ IB_QPT_UC ; 
 scalar_t__ qp_type (struct rxe_qp*) ; 
 struct rxe_dev* to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int get_mtu(struct rxe_qp *qp)
{
	struct rxe_dev *rxe = to_rdev(qp->ibqp.device);

	if ((qp_type(qp) == IB_QPT_RC) || (qp_type(qp) == IB_QPT_UC))
		return qp->mtu;

	return rxe->port.mtu_cap;
}