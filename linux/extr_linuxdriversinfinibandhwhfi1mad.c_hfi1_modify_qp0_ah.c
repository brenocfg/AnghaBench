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
typedef  int /*<<< orphan*/  u32 ;
struct rvt_qp {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct rvt_ah {TYPE_2__ ibah; } ;
struct rdma_ah_attr {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/ * qp; } ;
struct hfi1_ibport {TYPE_1__ rvp; } ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  hfi1_update_sm_ah_attr (struct hfi1_ibport*,struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rdma_ah_attr*,int /*<<< orphan*/ ,int) ; 
 struct rvt_qp* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int rdma_modify_ah (TYPE_2__*,struct rdma_ah_attr*) ; 

__attribute__((used)) static int hfi1_modify_qp0_ah(struct hfi1_ibport *ibp,
			      struct rvt_ah *ah, u32 dlid)
{
	struct rdma_ah_attr attr;
	struct rvt_qp *qp0;
	int ret = -EINVAL;

	memset(&attr, 0, sizeof(attr));
	attr.type = ah->ibah.type;
	hfi1_update_sm_ah_attr(ibp, &attr, dlid);
	rcu_read_lock();
	qp0 = rcu_dereference(ibp->rvp.qp[0]);
	if (qp0)
		ret = rdma_modify_ah(&ah->ibah, &attr);
	rcu_read_unlock();
	return ret;
}