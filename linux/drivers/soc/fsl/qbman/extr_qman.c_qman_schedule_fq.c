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
union qm_mc_result {int verb; scalar_t__ result; } ;
union qm_mc_command {int /*<<< orphan*/  fq; } ;
struct qman_portal {TYPE_1__* config; int /*<<< orphan*/  p; } ;
struct qman_fq {scalar_t__ state; int /*<<< orphan*/  fqid; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  QMAN_FQ_FLAG_NO_MODIFY ; 
 int /*<<< orphan*/  QMAN_FQ_STATE_CHANGING ; 
 int /*<<< orphan*/  QM_MCC_VERB_ALTER_SCHED ; 
 scalar_t__ QM_MCR_RESULT_OK ; 
 int QM_MCR_VERB_ALTER_SCHED ; 
 int QM_MCR_VERB_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fq_isset (struct qman_fq*,int /*<<< orphan*/ ) ; 
 struct qman_portal* get_affine_portal () ; 
 int /*<<< orphan*/  put_affine_portal () ; 
 int /*<<< orphan*/  qm_fqid_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_mc_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_mc_result_timeout (int /*<<< orphan*/ *,union qm_mc_result**) ; 
 union qm_mc_command* qm_mc_start (int /*<<< orphan*/ *) ; 
 scalar_t__ qman_fq_state_parked ; 
 scalar_t__ qman_fq_state_sched ; 

int qman_schedule_fq(struct qman_fq *fq)
{
	union qm_mc_command *mcc;
	union qm_mc_result *mcr;
	struct qman_portal *p;
	int ret = 0;

	if (fq->state != qman_fq_state_parked)
		return -EINVAL;
#ifdef CONFIG_FSL_DPAA_CHECKING
	if (fq_isset(fq, QMAN_FQ_FLAG_NO_MODIFY))
		return -EINVAL;
#endif
	/* Issue a ALTERFQ_SCHED management command */
	p = get_affine_portal();
	if (fq_isset(fq, QMAN_FQ_STATE_CHANGING) ||
	    fq->state != qman_fq_state_parked) {
		ret = -EBUSY;
		goto out;
	}
	mcc = qm_mc_start(&p->p);
	qm_fqid_set(&mcc->fq, fq->fqid);
	qm_mc_commit(&p->p, QM_MCC_VERB_ALTER_SCHED);
	if (!qm_mc_result_timeout(&p->p, &mcr)) {
		dev_err(p->config->dev, "ALTER_SCHED timeout\n");
		ret = -ETIMEDOUT;
		goto out;
	}

	DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) == QM_MCR_VERB_ALTER_SCHED);
	if (mcr->result != QM_MCR_RESULT_OK) {
		ret = -EIO;
		goto out;
	}
	fq->state = qman_fq_state_sched;
out:
	put_affine_portal();
	return ret;
}