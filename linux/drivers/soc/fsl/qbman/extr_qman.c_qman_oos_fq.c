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
union qm_mc_result {int verb; scalar_t__ result; } ;
union qm_mc_command {int /*<<< orphan*/  fq; } ;
struct qman_portal {int /*<<< orphan*/  p; } ;
struct qman_fq {scalar_t__ state; int /*<<< orphan*/  fqid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  QMAN_FQ_FLAG_NO_MODIFY ; 
 int /*<<< orphan*/  QMAN_FQ_STATE_BLOCKOOS ; 
 int /*<<< orphan*/  QM_MCC_VERB_ALTER_OOS ; 
 scalar_t__ QM_MCR_RESULT_OK ; 
 int QM_MCR_VERB_ALTER_OOS ; 
 int QM_MCR_VERB_MASK ; 
 scalar_t__ fq_isset (struct qman_fq*,int /*<<< orphan*/ ) ; 
 struct qman_portal* get_affine_portal () ; 
 int /*<<< orphan*/  put_affine_portal () ; 
 int /*<<< orphan*/  qm_fqid_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_mc_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_mc_result_timeout (int /*<<< orphan*/ *,union qm_mc_result**) ; 
 union qm_mc_command* qm_mc_start (int /*<<< orphan*/ *) ; 
 scalar_t__ qman_fq_state_oos ; 
 scalar_t__ qman_fq_state_retired ; 

int qman_oos_fq(struct qman_fq *fq)
{
	union qm_mc_command *mcc;
	union qm_mc_result *mcr;
	struct qman_portal *p;
	int ret = 0;

	if (fq->state != qman_fq_state_retired)
		return -EINVAL;
#ifdef CONFIG_FSL_DPAA_CHECKING
	if (fq_isset(fq, QMAN_FQ_FLAG_NO_MODIFY))
		return -EINVAL;
#endif
	p = get_affine_portal();
	if (fq_isset(fq, QMAN_FQ_STATE_BLOCKOOS) ||
	    fq->state != qman_fq_state_retired) {
		ret = -EBUSY;
		goto out;
	}
	mcc = qm_mc_start(&p->p);
	qm_fqid_set(&mcc->fq, fq->fqid);
	qm_mc_commit(&p->p, QM_MCC_VERB_ALTER_OOS);
	if (!qm_mc_result_timeout(&p->p, &mcr)) {
		ret = -ETIMEDOUT;
		goto out;
	}
	DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) == QM_MCR_VERB_ALTER_OOS);
	if (mcr->result != QM_MCR_RESULT_OK) {
		ret = -EIO;
		goto out;
	}
	fq->state = qman_fq_state_oos;
out:
	put_affine_portal();
	return ret;
}