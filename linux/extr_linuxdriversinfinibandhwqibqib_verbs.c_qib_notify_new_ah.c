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
struct rvt_ah {int /*<<< orphan*/  log_pmtu; int /*<<< orphan*/  attr; int /*<<< orphan*/  vl; } ;
struct rdma_ah_attr {int dummy; } ;
struct qib_pportdata {int /*<<< orphan*/  ibmtu; } ;
struct qib_ibport {int /*<<< orphan*/ * sl_to_vl; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 struct qib_pportdata* ppd_from_ibp (struct qib_ibport*) ; 
 int /*<<< orphan*/  rdma_ah_get_port_num (struct rdma_ah_attr*) ; 
 size_t rdma_ah_get_sl (int /*<<< orphan*/ *) ; 
 struct qib_ibport* to_iport (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qib_notify_new_ah(struct ib_device *ibdev,
			      struct rdma_ah_attr *ah_attr,
			      struct rvt_ah *ah)
{
	struct qib_ibport *ibp;
	struct qib_pportdata *ppd;

	/*
	 * Do not trust reading anything from rvt_ah at this point as it is not
	 * done being setup. We can however modify things which we need to set.
	 */

	ibp = to_iport(ibdev, rdma_ah_get_port_num(ah_attr));
	ppd = ppd_from_ibp(ibp);
	ah->vl = ibp->sl_to_vl[rdma_ah_get_sl(&ah->attr)];
	ah->log_pmtu = ilog2(ppd->ibmtu);
}