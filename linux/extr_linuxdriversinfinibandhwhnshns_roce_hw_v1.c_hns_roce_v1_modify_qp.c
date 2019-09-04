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
struct ib_qp_attr {int dummy; } ;
struct ib_qp {scalar_t__ qp_type; } ;
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;

/* Variables and functions */
 scalar_t__ IB_QPT_GSI ; 
 scalar_t__ IB_QPT_SMI ; 
 int hns_roce_v1_m_qp (struct ib_qp*,struct ib_qp_attr const*,int,int,int) ; 
 int hns_roce_v1_m_sqp (struct ib_qp*,struct ib_qp_attr const*,int,int,int) ; 

__attribute__((used)) static int hns_roce_v1_modify_qp(struct ib_qp *ibqp,
				 const struct ib_qp_attr *attr, int attr_mask,
				 enum ib_qp_state cur_state,
				 enum ib_qp_state new_state)
{

	if (ibqp->qp_type == IB_QPT_GSI || ibqp->qp_type == IB_QPT_SMI)
		return hns_roce_v1_m_sqp(ibqp, attr, attr_mask, cur_state,
					 new_state);
	else
		return hns_roce_v1_m_qp(ibqp, attr, attr_mask, cur_state,
					new_state);
}