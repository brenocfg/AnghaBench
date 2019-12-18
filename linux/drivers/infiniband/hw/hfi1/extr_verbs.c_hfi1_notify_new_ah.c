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
typedef  int /*<<< orphan*/  u8 ;
struct rdma_ah_attr {int dummy; } ;
struct rvt_ah {int vl; int /*<<< orphan*/  log_pmtu; struct rdma_ah_attr attr; } ;
struct ib_device {int dummy; } ;
struct hfi1_pportdata {int dummy; } ;
struct hfi1_ibport {int /*<<< orphan*/ * sl_to_sc; } ;
struct hfi1_devdata {TYPE_1__* vld; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 struct hfi1_devdata* dd_from_ppd (struct hfi1_pportdata*) ; 
 int /*<<< orphan*/  hfi1_make_opa_lid (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  hfi1_update_ah_attr (struct ib_device*,struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 int num_vls ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 
 int /*<<< orphan*/  rdma_ah_get_port_num (struct rdma_ah_attr*) ; 
 size_t rdma_ah_get_sl (struct rdma_ah_attr*) ; 
 int sc_to_vlt (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 struct hfi1_ibport* to_iport (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hfi1_notify_new_ah(struct ib_device *ibdev,
			       struct rdma_ah_attr *ah_attr,
			       struct rvt_ah *ah)
{
	struct hfi1_ibport *ibp;
	struct hfi1_pportdata *ppd;
	struct hfi1_devdata *dd;
	u8 sc5;
	struct rdma_ah_attr *attr = &ah->attr;

	/*
	 * Do not trust reading anything from rvt_ah at this point as it is not
	 * done being setup. We can however modify things which we need to set.
	 */

	ibp = to_iport(ibdev, rdma_ah_get_port_num(ah_attr));
	ppd = ppd_from_ibp(ibp);
	sc5 = ibp->sl_to_sc[rdma_ah_get_sl(&ah->attr)];
	hfi1_update_ah_attr(ibdev, attr);
	hfi1_make_opa_lid(attr);
	dd = dd_from_ppd(ppd);
	ah->vl = sc_to_vlt(dd, sc5);
	if (ah->vl < num_vls || ah->vl == 15)
		ah->log_pmtu = ilog2(dd->vld[ah->vl].mtu);
}