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
typedef  int /*<<< orphan*/  u64 ;
struct rvt_qp {struct hfi1_qp_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  local; } ;
struct hfi1_qp_priv {TYPE_1__ tid_rdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  tid_rdma_opfn_encode (int /*<<< orphan*/ *) ; 

bool tid_rdma_conn_req(struct rvt_qp *qp, u64 *data)
{
	struct hfi1_qp_priv *priv = qp->priv;

	*data = tid_rdma_opfn_encode(&priv->tid_rdma.local);
	return true;
}