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
struct tid_rdma_params {int dummy; } ;
struct rvt_qp {struct hfi1_qp_priv* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  remote; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct hfi1_qp_priv {TYPE_2__ tid_rdma; TYPE_1__ opfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct tid_rdma_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct tid_rdma_params* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_head ; 

void tid_rdma_conn_error(struct rvt_qp *qp)
{
	struct hfi1_qp_priv *priv = qp->priv;
	struct tid_rdma_params *old;

	old = rcu_dereference_protected(priv->tid_rdma.remote,
					lockdep_is_held(&priv->opfn.lock));
	RCU_INIT_POINTER(priv->tid_rdma.remote, NULL);
	if (old)
		kfree_rcu(old, rcu_head);
}