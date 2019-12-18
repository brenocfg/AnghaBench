#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int /*<<< orphan*/  pd; } ;
struct rvt_qp {TYPE_4__ ibqp; } ;
struct rdma_ah_attr {int /*<<< orphan*/  type; } ;
struct ib_ah {int dummy; } ;
struct hfi1_pportdata {int /*<<< orphan*/  port; } ;
struct TYPE_7__ {int /*<<< orphan*/ * qp; } ;
struct hfi1_ibport {TYPE_3__ rvp; } ;
struct TYPE_5__ {int /*<<< orphan*/  ibdev; } ;
struct TYPE_6__ {TYPE_1__ rdi; } ;
struct hfi1_devdata {TYPE_2__ verbs_dev; } ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct ib_ah* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct hfi1_devdata* dd_from_ppd (struct hfi1_pportdata*) ; 
 int /*<<< orphan*/  hfi1_update_sm_ah_attr (struct hfi1_ibport*,struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rdma_ah_attr*,int /*<<< orphan*/ ,int) ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 
 struct rvt_qp* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rdma_ah_find_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ib_ah* rdma_create_ah (int /*<<< orphan*/ ,struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ib_ah *hfi1_create_qp0_ah(struct hfi1_ibport *ibp, u32 dlid)
{
	struct rdma_ah_attr attr;
	struct ib_ah *ah = ERR_PTR(-EINVAL);
	struct rvt_qp *qp0;
	struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	struct hfi1_devdata *dd = dd_from_ppd(ppd);
	u8 port_num = ppd->port;

	memset(&attr, 0, sizeof(attr));
	attr.type = rdma_ah_find_type(&dd->verbs_dev.rdi.ibdev, port_num);
	hfi1_update_sm_ah_attr(ibp, &attr, dlid);
	rcu_read_lock();
	qp0 = rcu_dereference(ibp->rvp.qp[0]);
	if (qp0)
		ah = rdma_create_ah(qp0->ibqp.pd, &attr, 0);
	rcu_read_unlock();
	return ah;
}