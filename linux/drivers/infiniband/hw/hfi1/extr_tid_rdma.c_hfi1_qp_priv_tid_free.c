#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct rvt_swqe {struct hfi1_ack_priv* priv; } ;
struct TYPE_4__ {scalar_t__ qp_type; } ;
struct rvt_qp {size_t s_size; TYPE_2__* s_ack_queue; TYPE_1__ ibqp; struct hfi1_qp_priv* priv; } ;
struct rvt_dev_info {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  opfn_work; } ;
struct hfi1_qp_priv {struct hfi1_ack_priv* pages; TYPE_3__ opfn; } ;
struct hfi1_ack_priv {int /*<<< orphan*/  tid_req; } ;
struct TYPE_5__ {struct hfi1_ack_priv* priv; } ;

/* Variables and functions */
 scalar_t__ HFI1_CAP_IS_KSET (int /*<<< orphan*/ ) ; 
 scalar_t__ IB_QPT_RC ; 
 int /*<<< orphan*/  TID_RDMA ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfi1_kern_exp_rcv_free_flows (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hfi1_ack_priv*) ; 
 struct rvt_swqe* rvt_get_swqe_ptr (struct rvt_qp*,size_t) ; 
 size_t rvt_max_atomic (struct rvt_dev_info*) ; 

void hfi1_qp_priv_tid_free(struct rvt_dev_info *rdi, struct rvt_qp *qp)
{
	struct hfi1_qp_priv *qpriv = qp->priv;
	struct rvt_swqe *wqe;
	u32 i;

	if (qp->ibqp.qp_type == IB_QPT_RC && HFI1_CAP_IS_KSET(TID_RDMA)) {
		for (i = 0; i < qp->s_size; i++) {
			wqe = rvt_get_swqe_ptr(qp, i);
			kfree(wqe->priv);
			wqe->priv = NULL;
		}
		for (i = 0; i < rvt_max_atomic(rdi); i++) {
			struct hfi1_ack_priv *priv = qp->s_ack_queue[i].priv;

			if (priv)
				hfi1_kern_exp_rcv_free_flows(&priv->tid_req);
			kfree(priv);
			qp->s_ack_queue[i].priv = NULL;
		}
		cancel_work_sync(&qpriv->opfn.opfn_work);
		kfree(qpriv->pages);
		qpriv->pages = NULL;
	}
}