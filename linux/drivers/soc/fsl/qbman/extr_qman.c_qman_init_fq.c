#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union qm_mc_result {scalar_t__ verb; scalar_t__ result; } ;
struct TYPE_5__ {int /*<<< orphan*/  cgid; int /*<<< orphan*/  fq_ctrl; int /*<<< orphan*/  context_a; int /*<<< orphan*/  context_b; } ;
struct qm_mcc_initfq {TYPE_2__ fqd; int /*<<< orphan*/  we_mask; scalar_t__ count; } ;
union qm_mc_command {struct qm_mcc_initfq initfq; int /*<<< orphan*/  fq; } ;
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct qman_portal {TYPE_1__* config; int /*<<< orphan*/  p; } ;
struct qman_fq {scalar_t__ state; int /*<<< orphan*/  cgr_groupid; int /*<<< orphan*/  fqid; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  QMAN_FQ_FLAG_NO_MODIFY ; 
 int /*<<< orphan*/  QMAN_FQ_FLAG_TO_DCPORTAL ; 
 int /*<<< orphan*/  QMAN_FQ_STATE_CGR_EN ; 
 int /*<<< orphan*/  QMAN_FQ_STATE_CHANGING ; 
 int QMAN_INITFQ_FLAG_LOCAL ; 
 int QMAN_INITFQ_FLAG_SCHED ; 
 int QM_FQCTRL_CGE ; 
 int QM_INITFQ_WE_CGID ; 
 int QM_INITFQ_WE_CONTEXTA ; 
 int QM_INITFQ_WE_CONTEXTB ; 
 int QM_INITFQ_WE_DESTWQ ; 
 int QM_INITFQ_WE_FQCTRL ; 
 int QM_INITFQ_WE_OAC ; 
 int QM_INITFQ_WE_TDTHRESH ; 
 scalar_t__ QM_MCC_VERB_INITFQ_PARKED ; 
 scalar_t__ QM_MCC_VERB_INITFQ_SCHED ; 
 scalar_t__ QM_MCR_RESULT_OK ; 
 scalar_t__ QM_MCR_VERB_MASK ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,struct qman_fq*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fq_clear (struct qman_fq*,int /*<<< orphan*/ ) ; 
 scalar_t__ fq_isclear (struct qman_fq*,int /*<<< orphan*/ ) ; 
 scalar_t__ fq_isset (struct qman_fq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fq_set (struct qman_fq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fq_to_tag (struct qman_fq*) ; 
 struct qman_portal* get_affine_portal () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_affine_portal () ; 
 int /*<<< orphan*/  qm_fqd_set_destwq (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qm_fqd_stashing_set64 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_fqid_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_mc_commit (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  qm_mc_result_timeout (int /*<<< orphan*/ *,union qm_mc_result**) ; 
 union qm_mc_command* qm_mc_start (int /*<<< orphan*/ *) ; 
 struct qman_portal* qman_dma_portal ; 
 scalar_t__ qman_fq_state_oos ; 
 scalar_t__ qman_fq_state_parked ; 
 scalar_t__ qman_fq_state_sched ; 

int qman_init_fq(struct qman_fq *fq, u32 flags, struct qm_mcc_initfq *opts)
{
	union qm_mc_command *mcc;
	union qm_mc_result *mcr;
	struct qman_portal *p;
	u8 res, myverb;
	int ret = 0;

	myverb = (flags & QMAN_INITFQ_FLAG_SCHED)
		? QM_MCC_VERB_INITFQ_SCHED : QM_MCC_VERB_INITFQ_PARKED;

	if (fq->state != qman_fq_state_oos &&
	    fq->state != qman_fq_state_parked)
		return -EINVAL;
#ifdef CONFIG_FSL_DPAA_CHECKING
	if (fq_isset(fq, QMAN_FQ_FLAG_NO_MODIFY))
		return -EINVAL;
#endif
	if (opts && (be16_to_cpu(opts->we_mask) & QM_INITFQ_WE_OAC)) {
		/* And can't be set at the same time as TDTHRESH */
		if (be16_to_cpu(opts->we_mask) & QM_INITFQ_WE_TDTHRESH)
			return -EINVAL;
	}
	/* Issue an INITFQ_[PARKED|SCHED] management command */
	p = get_affine_portal();
	if (fq_isset(fq, QMAN_FQ_STATE_CHANGING) ||
	    (fq->state != qman_fq_state_oos &&
	     fq->state != qman_fq_state_parked)) {
		ret = -EBUSY;
		goto out;
	}
	mcc = qm_mc_start(&p->p);
	if (opts)
		mcc->initfq = *opts;
	qm_fqid_set(&mcc->fq, fq->fqid);
	mcc->initfq.count = 0;
	/*
	 * If the FQ does *not* have the TO_DCPORTAL flag, context_b is set as a
	 * demux pointer. Otherwise, the caller-provided value is allowed to
	 * stand, don't overwrite it.
	 */
	if (fq_isclear(fq, QMAN_FQ_FLAG_TO_DCPORTAL)) {
		dma_addr_t phys_fq;

		mcc->initfq.we_mask |= cpu_to_be16(QM_INITFQ_WE_CONTEXTB);
		mcc->initfq.fqd.context_b = cpu_to_be32(fq_to_tag(fq));
		/*
		 *  and the physical address - NB, if the user wasn't trying to
		 * set CONTEXTA, clear the stashing settings.
		 */
		if (!(be16_to_cpu(mcc->initfq.we_mask) &
				  QM_INITFQ_WE_CONTEXTA)) {
			mcc->initfq.we_mask |=
				cpu_to_be16(QM_INITFQ_WE_CONTEXTA);
			memset(&mcc->initfq.fqd.context_a, 0,
				sizeof(mcc->initfq.fqd.context_a));
		} else {
			struct qman_portal *p = qman_dma_portal;

			phys_fq = dma_map_single(p->config->dev, fq,
						 sizeof(*fq), DMA_TO_DEVICE);
			if (dma_mapping_error(p->config->dev, phys_fq)) {
				dev_err(p->config->dev, "dma_mapping failed\n");
				ret = -EIO;
				goto out;
			}

			qm_fqd_stashing_set64(&mcc->initfq.fqd, phys_fq);
		}
	}
	if (flags & QMAN_INITFQ_FLAG_LOCAL) {
		int wq = 0;

		if (!(be16_to_cpu(mcc->initfq.we_mask) &
				  QM_INITFQ_WE_DESTWQ)) {
			mcc->initfq.we_mask |=
				cpu_to_be16(QM_INITFQ_WE_DESTWQ);
			wq = 4;
		}
		qm_fqd_set_destwq(&mcc->initfq.fqd, p->config->channel, wq);
	}
	qm_mc_commit(&p->p, myverb);
	if (!qm_mc_result_timeout(&p->p, &mcr)) {
		dev_err(p->config->dev, "MCR timeout\n");
		ret = -ETIMEDOUT;
		goto out;
	}

	DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) == myverb);
	res = mcr->result;
	if (res != QM_MCR_RESULT_OK) {
		ret = -EIO;
		goto out;
	}
	if (opts) {
		if (be16_to_cpu(opts->we_mask) & QM_INITFQ_WE_FQCTRL) {
			if (be16_to_cpu(opts->fqd.fq_ctrl) & QM_FQCTRL_CGE)
				fq_set(fq, QMAN_FQ_STATE_CGR_EN);
			else
				fq_clear(fq, QMAN_FQ_STATE_CGR_EN);
		}
		if (be16_to_cpu(opts->we_mask) & QM_INITFQ_WE_CGID)
			fq->cgr_groupid = opts->fqd.cgid;
	}
	fq->state = (flags & QMAN_INITFQ_FLAG_SCHED) ?
		qman_fq_state_sched : qman_fq_state_parked;

out:
	put_affine_portal();
	return ret;
}