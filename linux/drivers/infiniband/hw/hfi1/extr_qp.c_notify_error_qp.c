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
struct rvt_qp {int s_flags; int /*<<< orphan*/ * s_rdma_mr; scalar_t__ s_hdrwords; struct hfi1_qp_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/ * lock; int /*<<< orphan*/  list; } ;
struct hfi1_qp_priv {int s_flags; TYPE_1__ s_iowait; } ;
typedef  int /*<<< orphan*/  seqlock_t ;

/* Variables and functions */
 int HFI1_S_ANY_WAIT_IO ; 
 int /*<<< orphan*/  IOWAIT_PENDING_IB ; 
 int /*<<< orphan*/  IOWAIT_PENDING_TID ; 
 int RVT_S_BUSY ; 
 int /*<<< orphan*/  flush_tx_list (struct rvt_qp*) ; 
 int /*<<< orphan*/  iowait_clear_flag (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_put_mr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_put_qp (struct rvt_qp*) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

void notify_error_qp(struct rvt_qp *qp)
{
	struct hfi1_qp_priv *priv = qp->priv;
	seqlock_t *lock = priv->s_iowait.lock;

	if (lock) {
		write_seqlock(lock);
		if (!list_empty(&priv->s_iowait.list) &&
		    !(qp->s_flags & RVT_S_BUSY) &&
		    !(priv->s_flags & RVT_S_BUSY)) {
			qp->s_flags &= ~HFI1_S_ANY_WAIT_IO;
			iowait_clear_flag(&priv->s_iowait, IOWAIT_PENDING_IB);
			iowait_clear_flag(&priv->s_iowait, IOWAIT_PENDING_TID);
			list_del_init(&priv->s_iowait.list);
			priv->s_iowait.lock = NULL;
			rvt_put_qp(qp);
		}
		write_sequnlock(lock);
	}

	if (!(qp->s_flags & RVT_S_BUSY) && !(priv->s_flags & RVT_S_BUSY)) {
		qp->s_hdrwords = 0;
		if (qp->s_rdma_mr) {
			rvt_put_mr(qp->s_rdma_mr);
			qp->s_rdma_mr = NULL;
		}
		flush_tx_list(qp);
	}
}