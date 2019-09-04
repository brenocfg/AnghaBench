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
struct ib_qp_init_attr {int dummy; } ;
struct ib_qp_attr {int dummy; } ;
struct ib_qp {int dummy; } ;
struct hns_roce_qp {int doorbell_qpn; } ;

/* Variables and functions */
 int hns_roce_v1_q_qp (struct ib_qp*,struct ib_qp_attr*,int,struct ib_qp_init_attr*) ; 
 int hns_roce_v1_q_sqp (struct ib_qp*,struct ib_qp_attr*,int,struct ib_qp_init_attr*) ; 
 struct hns_roce_qp* to_hr_qp (struct ib_qp*) ; 

__attribute__((used)) static int hns_roce_v1_query_qp(struct ib_qp *ibqp, struct ib_qp_attr *qp_attr,
				int qp_attr_mask,
				struct ib_qp_init_attr *qp_init_attr)
{
	struct hns_roce_qp *hr_qp = to_hr_qp(ibqp);

	return hr_qp->doorbell_qpn <= 1 ?
		hns_roce_v1_q_sqp(ibqp, qp_attr, qp_attr_mask, qp_init_attr) :
		hns_roce_v1_q_qp(ibqp, qp_attr, qp_attr_mask, qp_init_attr);
}