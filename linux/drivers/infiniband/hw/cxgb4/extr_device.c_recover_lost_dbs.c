#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  pdev; } ;
struct uld_ctx {TYPE_2__ lldi; } ;
struct qp_list {int idx; struct c4iw_qp** qps; } ;
struct TYPE_13__ {scalar_t__ wq_pidx_inc; int /*<<< orphan*/  qid; } ;
struct TYPE_11__ {scalar_t__ wq_pidx_inc; int /*<<< orphan*/  qid; } ;
struct TYPE_17__ {TYPE_3__ rq; TYPE_1__ sq; } ;
struct c4iw_qp {TYPE_6__* rhp; int /*<<< orphan*/  lock; TYPE_7__ wq; } ;
struct TYPE_14__ {int /*<<< orphan*/ * ports; } ;
struct TYPE_15__ {TYPE_4__ lldi; } ;
struct TYPE_16__ {TYPE_5__ rdev; int /*<<< orphan*/  qps; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 scalar_t__ cxgb4_dbfifo_count (int /*<<< orphan*/ ,int) ; 
 int cxgb4_sync_txq_pidx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_rq_host_wq_pidx (TYPE_7__*) ; 
 int /*<<< orphan*/  t4_rq_wq_size (TYPE_7__*) ; 
 int /*<<< orphan*/  t4_sq_host_wq_pidx (TYPE_7__*) ; 
 int /*<<< orphan*/  t4_sq_wq_size (TYPE_7__*) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int) ; 
 int /*<<< orphan*/  xa_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void recover_lost_dbs(struct uld_ctx *ctx, struct qp_list *qp_list)
{
	int idx;
	int ret;

	for (idx = 0; idx < qp_list->idx; idx++) {
		struct c4iw_qp *qp = qp_list->qps[idx];

		xa_lock_irq(&qp->rhp->qps);
		spin_lock(&qp->lock);
		ret = cxgb4_sync_txq_pidx(qp->rhp->rdev.lldi.ports[0],
					  qp->wq.sq.qid,
					  t4_sq_host_wq_pidx(&qp->wq),
					  t4_sq_wq_size(&qp->wq));
		if (ret) {
			pr_err("%s: Fatal error - DB overflow recovery failed - error syncing SQ qid %u\n",
			       pci_name(ctx->lldi.pdev), qp->wq.sq.qid);
			spin_unlock(&qp->lock);
			xa_unlock_irq(&qp->rhp->qps);
			return;
		}
		qp->wq.sq.wq_pidx_inc = 0;

		ret = cxgb4_sync_txq_pidx(qp->rhp->rdev.lldi.ports[0],
					  qp->wq.rq.qid,
					  t4_rq_host_wq_pidx(&qp->wq),
					  t4_rq_wq_size(&qp->wq));

		if (ret) {
			pr_err("%s: Fatal error - DB overflow recovery failed - error syncing RQ qid %u\n",
			       pci_name(ctx->lldi.pdev), qp->wq.rq.qid);
			spin_unlock(&qp->lock);
			xa_unlock_irq(&qp->rhp->qps);
			return;
		}
		qp->wq.rq.wq_pidx_inc = 0;
		spin_unlock(&qp->lock);
		xa_unlock_irq(&qp->rhp->qps);

		/* Wait for the dbfifo to drain */
		while (cxgb4_dbfifo_count(qp->rhp->rdev.lldi.ports[0], 1) > 0) {
			set_current_state(TASK_UNINTERRUPTIBLE);
			schedule_timeout(usecs_to_jiffies(10));
		}
	}
}