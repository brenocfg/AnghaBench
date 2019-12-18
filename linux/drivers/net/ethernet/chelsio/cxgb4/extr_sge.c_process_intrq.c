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
typedef  int u32 ;
struct sge_rspq {int iqe_len; int /*<<< orphan*/ * bar2_addr; int /*<<< orphan*/  bar2_qid; int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  intr_params; scalar_t__ cur_desc; } ;
struct rsp_ctrl {int /*<<< orphan*/  pldbuflen_qid; int /*<<< orphan*/  type_gen; } ;
struct TYPE_4__ {int /*<<< orphan*/  intrq_lock; TYPE_1__** ingr_map; scalar_t__ ingr_start; struct sge_rspq intrq; } ;
struct adapter {TYPE_2__ sge; } ;
struct TYPE_3__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int CIDXINC_V (unsigned int) ; 
 int INGRESSQID_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ RSPD_TYPE_G (int /*<<< orphan*/ ) ; 
 scalar_t__ RSPD_TYPE_INTR_X ; 
 int SEINTARM_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SGE_PF_GTS_A ; 
 int SGE_UDB_GTS ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  is_new_response (struct rsp_ctrl const*,struct sge_rspq*) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rspq_next (struct sge_rspq*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int process_intrq(struct adapter *adap)
{
	unsigned int credits;
	const struct rsp_ctrl *rc;
	struct sge_rspq *q = &adap->sge.intrq;
	u32 val;

	spin_lock(&adap->sge.intrq_lock);
	for (credits = 0; ; credits++) {
		rc = (void *)q->cur_desc + (q->iqe_len - sizeof(*rc));
		if (!is_new_response(rc, q))
			break;

		dma_rmb();
		if (RSPD_TYPE_G(rc->type_gen) == RSPD_TYPE_INTR_X) {
			unsigned int qid = ntohl(rc->pldbuflen_qid);

			qid -= adap->sge.ingr_start;
			napi_schedule(&adap->sge.ingr_map[qid]->napi);
		}

		rspq_next(q);
	}

	val =  CIDXINC_V(credits) | SEINTARM_V(q->intr_params);

	/* If we don't have access to the new User GTS (T5+), use the old
	 * doorbell mechanism; otherwise use the new BAR2 mechanism.
	 */
	if (unlikely(q->bar2_addr == NULL)) {
		t4_write_reg(adap, MYPF_REG(SGE_PF_GTS_A),
			     val | INGRESSQID_V(q->cntxt_id));
	} else {
		writel(val | INGRESSQID_V(q->bar2_qid),
		       q->bar2_addr + SGE_UDB_GTS);
		wmb();
	}
	spin_unlock(&adap->sge.intrq_lock);
	return credits;
}