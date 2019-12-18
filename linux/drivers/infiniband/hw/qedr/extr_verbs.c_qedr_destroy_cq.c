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
struct qedr_dev {int /*<<< orphan*/  cdev; TYPE_2__* ops; int /*<<< orphan*/  rdma_ctx; } ;
struct TYPE_6__ {int /*<<< orphan*/  umem; int /*<<< orphan*/  pbl_tbl; int /*<<< orphan*/  pbl_info; } ;
struct qedr_cq {int destroyed; scalar_t__ cq_type; int /*<<< orphan*/  cnq_notif; TYPE_3__ q; int /*<<< orphan*/  pbl; int /*<<< orphan*/  icid; } ;
struct qed_rdma_destroy_cq_out_params {scalar_t__ num_cq_notif; } ;
struct qed_rdma_destroy_cq_in_params {int /*<<< orphan*/  icid; } ;
struct ib_udata {int dummy; } ;
struct ib_cq {int /*<<< orphan*/  device; } ;
struct TYPE_5__ {TYPE_1__* common; int /*<<< orphan*/  (* rdma_destroy_cq ) (int /*<<< orphan*/ ,struct qed_rdma_destroy_cq_in_params*,struct qed_rdma_destroy_cq_out_params*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* chain_free ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,struct qedr_cq*,int /*<<< orphan*/ ) ; 
 scalar_t__ QEDR_CQ_TYPE_GSI ; 
 int /*<<< orphan*/  QEDR_DESTROY_CQ_ITER_DURATION ; 
 int QEDR_DESTROY_CQ_MAX_ITERATIONS ; 
 int /*<<< orphan*/  QEDR_MSG_CQ ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 struct qedr_cq* get_qedr_cq (struct ib_cq*) ; 
 struct qedr_dev* get_qedr_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedr_free_pbl (struct qedr_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct qed_rdma_destroy_cq_in_params*,struct qed_rdma_destroy_cq_out_params*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

void qedr_destroy_cq(struct ib_cq *ibcq, struct ib_udata *udata)
{
	struct qedr_dev *dev = get_qedr_dev(ibcq->device);
	struct qed_rdma_destroy_cq_out_params oparams;
	struct qed_rdma_destroy_cq_in_params iparams;
	struct qedr_cq *cq = get_qedr_cq(ibcq);
	int iter;

	DP_DEBUG(dev, QEDR_MSG_CQ, "destroy cq %p (icid=%d)\n", cq, cq->icid);

	cq->destroyed = 1;

	/* GSIs CQs are handled by driver, so they don't exist in the FW */
	if (cq->cq_type == QEDR_CQ_TYPE_GSI)
		return;

	iparams.icid = cq->icid;
	dev->ops->rdma_destroy_cq(dev->rdma_ctx, &iparams, &oparams);
	dev->ops->common->chain_free(dev->cdev, &cq->pbl);

	if (udata) {
		qedr_free_pbl(dev, &cq->q.pbl_info, cq->q.pbl_tbl);
		ib_umem_release(cq->q.umem);
	}

	/* We don't want the IRQ handler to handle a non-existing CQ so we
	 * wait until all CNQ interrupts, if any, are received. This will always
	 * happen and will always happen very fast. If not, then a serious error
	 * has occured. That is why we can use a long delay.
	 * We spin for a short time so we don’t lose time on context switching
	 * in case all the completions are handled in that span. Otherwise
	 * we sleep for a while and check again. Since the CNQ may be
	 * associated with (only) the current CPU we use msleep to allow the
	 * current CPU to be freed.
	 * The CNQ notification is increased in qedr_irq_handler().
	 */
	iter = QEDR_DESTROY_CQ_MAX_ITERATIONS;
	while (oparams.num_cq_notif != READ_ONCE(cq->cnq_notif) && iter) {
		udelay(QEDR_DESTROY_CQ_ITER_DURATION);
		iter--;
	}

	iter = QEDR_DESTROY_CQ_MAX_ITERATIONS;
	while (oparams.num_cq_notif != READ_ONCE(cq->cnq_notif) && iter) {
		msleep(QEDR_DESTROY_CQ_ITER_DURATION);
		iter--;
	}

	/* Note that we don't need to have explicit code to wait for the
	 * completion of the event handler because it is invoked from the EQ.
	 * Since the destroy CQ ramrod has also been received on the EQ we can
	 * be certain that there's no event handler in process.
	 */
}