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
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct rvt_qp {int /*<<< orphan*/  remote_ah_attr; int /*<<< orphan*/  port_num; TYPE_1__ ibqp; struct hfi1_qp_priv* priv; } ;
struct hfi1_qp_priv {int /*<<< orphan*/  hdr_type; } ;
struct hfi1_pportdata {int /*<<< orphan*/  lid; } ;
struct hfi1_ibport {int dummy; } ;

/* Variables and functions */
 int IB_AH_GRH ; 
 int /*<<< orphan*/  hfi1_get_hdr_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfi1_make_opa_lid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfi1_update_ah_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 
 int rdma_ah_get_ah_flags (int /*<<< orphan*/ *) ; 
 struct hfi1_ibport* to_iport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void qp_set_16b(struct rvt_qp *qp)
{
	struct hfi1_pportdata *ppd;
	struct hfi1_ibport *ibp;
	struct hfi1_qp_priv *priv = qp->priv;

	/* Update ah_attr to account for extended LIDs */
	hfi1_update_ah_attr(qp->ibqp.device, &qp->remote_ah_attr);

	/* Create 32 bit LIDs */
	hfi1_make_opa_lid(&qp->remote_ah_attr);

	if (!(rdma_ah_get_ah_flags(&qp->remote_ah_attr) & IB_AH_GRH))
		return;

	ibp = to_iport(qp->ibqp.device, qp->port_num);
	ppd = ppd_from_ibp(ibp);
	priv->hdr_type = hfi1_get_hdr_type(ppd->lid, &qp->remote_ah_attr);
}