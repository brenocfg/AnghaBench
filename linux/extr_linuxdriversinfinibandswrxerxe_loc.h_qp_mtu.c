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
struct TYPE_4__ {int path_mtu; } ;
struct TYPE_3__ {scalar_t__ qp_type; } ;
struct rxe_qp {TYPE_2__ attr; TYPE_1__ ibqp; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ IB_QPT_UC ; 
 int RXE_PORT_MAX_MTU ; 

__attribute__((used)) static inline int qp_mtu(struct rxe_qp *qp)
{
	if (qp->ibqp.qp_type == IB_QPT_RC || qp->ibqp.qp_type == IB_QPT_UC)
		return qp->attr.path_mtu;
	else
		return RXE_PORT_MAX_MTU;
}