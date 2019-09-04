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
typedef  int u32 ;
struct sge_rspq {int iqe_len; unsigned int abs_id; scalar_t__ bar2_addr; int /*<<< orphan*/  bar2_qid; int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  intr_params; int /*<<< orphan*/  napi; scalar_t__ cur_desc; } ;
struct sge {int /*<<< orphan*/  intrq_lock; struct sge_rspq** ingr_map; struct sge_rspq intrq; } ;
struct rsp_ctrl {int /*<<< orphan*/  pldbuflen_qid; int /*<<< orphan*/  type_gen; } ;
struct adapter {struct sge sge; int /*<<< orphan*/  pdev_dev; } ;

/* Variables and functions */
 int CIDXINC_V (unsigned int) ; 
 int INGRESSQID_V (int /*<<< orphan*/ ) ; 
 unsigned int IQ_IDX (struct sge*,unsigned int) ; 
 unsigned int MAX_INGQ ; 
 unsigned int RSPD_QID_G (int /*<<< orphan*/ ) ; 
 scalar_t__ RSPD_TYPE_G (int /*<<< orphan*/ ) ; 
 scalar_t__ RSPD_TYPE_INTR_X ; 
 int SEINTARM_V (int /*<<< orphan*/ ) ; 
 scalar_t__ SGE_UDB_GTS ; 
 scalar_t__ SGE_VF_GTS ; 
 scalar_t__ T4VF_SGE_BASE_ADDR ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  is_new_response (struct rsp_ctrl const*,struct sge_rspq*) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rspq_next (struct sge_rspq*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,scalar_t__,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static unsigned int process_intrq(struct adapter *adapter)
{
	struct sge *s = &adapter->sge;
	struct sge_rspq *intrq = &s->intrq;
	unsigned int work_done;
	u32 val;

	spin_lock(&adapter->sge.intrq_lock);
	for (work_done = 0; ; work_done++) {
		const struct rsp_ctrl *rc;
		unsigned int qid, iq_idx;
		struct sge_rspq *rspq;

		/*
		 * Grab the next response from the interrupt queue and bail
		 * out if it's not a new response.
		 */
		rc = (void *)intrq->cur_desc + (intrq->iqe_len - sizeof(*rc));
		if (!is_new_response(rc, intrq))
			break;

		/*
		 * If the response isn't a forwarded interrupt message issue a
		 * error and go on to the next response message.  This should
		 * never happen ...
		 */
		dma_rmb();
		if (unlikely(RSPD_TYPE_G(rc->type_gen) != RSPD_TYPE_INTR_X)) {
			dev_err(adapter->pdev_dev,
				"Unexpected INTRQ response type %d\n",
				RSPD_TYPE_G(rc->type_gen));
			continue;
		}

		/*
		 * Extract the Queue ID from the interrupt message and perform
		 * sanity checking to make sure it really refers to one of our
		 * Ingress Queues which is active and matches the queue's ID.
		 * None of these error conditions should ever happen so we may
		 * want to either make them fatal and/or conditionalized under
		 * DEBUG.
		 */
		qid = RSPD_QID_G(be32_to_cpu(rc->pldbuflen_qid));
		iq_idx = IQ_IDX(s, qid);
		if (unlikely(iq_idx >= MAX_INGQ)) {
			dev_err(adapter->pdev_dev,
				"Ingress QID %d out of range\n", qid);
			continue;
		}
		rspq = s->ingr_map[iq_idx];
		if (unlikely(rspq == NULL)) {
			dev_err(adapter->pdev_dev,
				"Ingress QID %d RSPQ=NULL\n", qid);
			continue;
		}
		if (unlikely(rspq->abs_id != qid)) {
			dev_err(adapter->pdev_dev,
				"Ingress QID %d refers to RSPQ %d\n",
				qid, rspq->abs_id);
			continue;
		}

		/*
		 * Schedule NAPI processing on the indicated Response Queue
		 * and move on to the next entry in the Forwarded Interrupt
		 * Queue.
		 */
		napi_schedule(&rspq->napi);
		rspq_next(intrq);
	}

	val = CIDXINC_V(work_done) | SEINTARM_V(intrq->intr_params);
	/* If we don't have access to the new User GTS (T5+), use the old
	 * doorbell mechanism; otherwise use the new BAR2 mechanism.
	 */
	if (unlikely(!intrq->bar2_addr)) {
		t4_write_reg(adapter, T4VF_SGE_BASE_ADDR + SGE_VF_GTS,
			     val | INGRESSQID_V(intrq->cntxt_id));
	} else {
		writel(val | INGRESSQID_V(intrq->bar2_qid),
		       intrq->bar2_addr + SGE_UDB_GTS);
		wmb();
	}

	spin_unlock(&adapter->sge.intrq_lock);

	return work_done;
}