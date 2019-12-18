#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int fqs; } ;
struct TYPE_7__ {int /*<<< orphan*/  fqd; } ;
struct TYPE_6__ {int state; } ;
union qm_mc_result {int verb; scalar_t__ result; TYPE_4__ alterfq; TYPE_3__ queryfq; TYPE_2__ queryfq_np; } ;
union qm_mc_command {int /*<<< orphan*/  fq; } ;
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct qman_portal {int sdqcr; int /*<<< orphan*/  p; TYPE_1__* config; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int EBUSY ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FQRL ; 
 int /*<<< orphan*/  FQRN ; 
 int /*<<< orphan*/  FQ_EMPTY ; 
 int /*<<< orphan*/  QM_MCC_VERB_ALTER_OOS ; 
 int /*<<< orphan*/  QM_MCC_VERB_ALTER_RETIRE ; 
 int /*<<< orphan*/  QM_MCC_VERB_QUERYFQ ; 
 int /*<<< orphan*/  QM_MCC_VERB_QUERYFQ_NP ; 
 int QM_MCR_FQS_NOTEMPTY ; 
 int QM_MCR_FQS_ORLPRESENT ; 
#define  QM_MCR_NP_STATE_ACTIVE 133 
 int QM_MCR_NP_STATE_MASK ; 
#define  QM_MCR_NP_STATE_OOS 132 
#define  QM_MCR_NP_STATE_PARKED 131 
#define  QM_MCR_NP_STATE_RETIRED 130 
#define  QM_MCR_NP_STATE_TEN_SCHED 129 
#define  QM_MCR_NP_STATE_TRU_SCHED 128 
 scalar_t__ QM_MCR_RESULT_OK ; 
 scalar_t__ QM_MCR_RESULT_PENDING ; 
 int QM_MCR_VERB_ALTER_OOS ; 
 int QM_MCR_VERB_ALTER_RETIRE ; 
 int QM_MCR_VERB_MASK ; 
 int QM_MCR_VERB_QUERYFQ ; 
 int QM_MCR_VERB_QUERYFQ_NP ; 
 int QM_SDQCR_CHANNELS_DEDICATED ; 
 int QM_SDQCR_CHANNELS_POOL_CONV (scalar_t__) ; 
 int QM_SDQCR_TYPE_ACTIVE ; 
 scalar_t__ QM_VDQCR_NUMFRAMES_SET (int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  drain_mr_fqrni (int /*<<< orphan*/ *) ; 
 struct qman_portal* get_affine_portal () ; 
 struct qman_portal* get_portal_for_channel (scalar_t__) ; 
 int /*<<< orphan*/  put_affine_portal () ; 
 scalar_t__ qm_channel_pool1 ; 
 int /*<<< orphan*/  qm_dqrr_drain_nomatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qm_dqrr_drain_wait (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_dqrr_sdqcr_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qm_dqrr_vdqcr_set (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ qm_fqd_get_chan (int /*<<< orphan*/ *) ; 
 scalar_t__ qm_fqd_get_wq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qm_fqid_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  qm_mc_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_mc_result_timeout (int /*<<< orphan*/ *,union qm_mc_result**) ; 
 union qm_mc_command* qm_mc_start (int /*<<< orphan*/ *) ; 
 int qm_mr_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int qman_shutdown_fq(u32 fqid)
{
	struct qman_portal *p, *channel_portal;
	struct device *dev;
	union qm_mc_command *mcc;
	union qm_mc_result *mcr;
	int orl_empty, drain = 0, ret = 0;
	u32 channel, wq, res;
	u8 state;

	p = get_affine_portal();
	dev = p->config->dev;
	/* Determine the state of the FQID */
	mcc = qm_mc_start(&p->p);
	qm_fqid_set(&mcc->fq, fqid);
	qm_mc_commit(&p->p, QM_MCC_VERB_QUERYFQ_NP);
	if (!qm_mc_result_timeout(&p->p, &mcr)) {
		dev_err(dev, "QUERYFQ_NP timeout\n");
		ret = -ETIMEDOUT;
		goto out;
	}

	DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) == QM_MCR_VERB_QUERYFQ_NP);
	state = mcr->queryfq_np.state & QM_MCR_NP_STATE_MASK;
	if (state == QM_MCR_NP_STATE_OOS)
		goto out; /* Already OOS, no need to do anymore checks */

	/* Query which channel the FQ is using */
	mcc = qm_mc_start(&p->p);
	qm_fqid_set(&mcc->fq, fqid);
	qm_mc_commit(&p->p, QM_MCC_VERB_QUERYFQ);
	if (!qm_mc_result_timeout(&p->p, &mcr)) {
		dev_err(dev, "QUERYFQ timeout\n");
		ret = -ETIMEDOUT;
		goto out;
	}

	DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) == QM_MCR_VERB_QUERYFQ);
	/* Need to store these since the MCR gets reused */
	channel = qm_fqd_get_chan(&mcr->queryfq.fqd);
	wq = qm_fqd_get_wq(&mcr->queryfq.fqd);

	if (channel < qm_channel_pool1) {
		channel_portal = get_portal_for_channel(channel);
		if (channel_portal == NULL) {
			dev_err(dev, "Can't find portal for dedicated channel 0x%x\n",
				channel);
			ret = -EIO;
			goto out;
		}
	} else
		channel_portal = p;

	switch (state) {
	case QM_MCR_NP_STATE_TEN_SCHED:
	case QM_MCR_NP_STATE_TRU_SCHED:
	case QM_MCR_NP_STATE_ACTIVE:
	case QM_MCR_NP_STATE_PARKED:
		orl_empty = 0;
		mcc = qm_mc_start(&channel_portal->p);
		qm_fqid_set(&mcc->fq, fqid);
		qm_mc_commit(&channel_portal->p, QM_MCC_VERB_ALTER_RETIRE);
		if (!qm_mc_result_timeout(&channel_portal->p, &mcr)) {
			dev_err(dev, "ALTER_RETIRE timeout\n");
			ret = -ETIMEDOUT;
			goto out;
		}
		DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) ==
			    QM_MCR_VERB_ALTER_RETIRE);
		res = mcr->result; /* Make a copy as we reuse MCR below */

		if (res == QM_MCR_RESULT_OK)
			drain_mr_fqrni(&channel_portal->p);

		if (res == QM_MCR_RESULT_PENDING) {
			/*
			 * Need to wait for the FQRN in the message ring, which
			 * will only occur once the FQ has been drained.  In
			 * order for the FQ to drain the portal needs to be set
			 * to dequeue from the channel the FQ is scheduled on
			 */
			int found_fqrn = 0;
			u16 dequeue_wq = 0;

			/* Flag that we need to drain FQ */
			drain = 1;

			if (channel >= qm_channel_pool1 &&
			    channel < qm_channel_pool1 + 15) {
				/* Pool channel, enable the bit in the portal */
				dequeue_wq = (channel -
					      qm_channel_pool1 + 1)<<4 | wq;
			} else if (channel < qm_channel_pool1) {
				/* Dedicated channel */
				dequeue_wq = wq;
			} else {
				dev_err(dev, "Can't recover FQ 0x%x, ch: 0x%x",
					fqid, channel);
				ret = -EBUSY;
				goto out;
			}
			/* Set the sdqcr to drain this channel */
			if (channel < qm_channel_pool1)
				qm_dqrr_sdqcr_set(&channel_portal->p,
						  QM_SDQCR_TYPE_ACTIVE |
						  QM_SDQCR_CHANNELS_DEDICATED);
			else
				qm_dqrr_sdqcr_set(&channel_portal->p,
						  QM_SDQCR_TYPE_ACTIVE |
						  QM_SDQCR_CHANNELS_POOL_CONV
						  (channel));
			do {
				/* Keep draining DQRR while checking the MR*/
				qm_dqrr_drain_nomatch(&channel_portal->p);
				/* Process message ring too */
				found_fqrn = qm_mr_drain(&channel_portal->p,
							 FQRN);
				cpu_relax();
			} while (!found_fqrn);
			/* Restore SDQCR */
			qm_dqrr_sdqcr_set(&channel_portal->p,
					  channel_portal->sdqcr);

		}
		if (res != QM_MCR_RESULT_OK &&
		    res != QM_MCR_RESULT_PENDING) {
			dev_err(dev, "retire_fq failed: FQ 0x%x, res=0x%x\n",
				fqid, res);
			ret = -EIO;
			goto out;
		}
		if (!(mcr->alterfq.fqs & QM_MCR_FQS_ORLPRESENT)) {
			/*
			 * ORL had no entries, no need to wait until the
			 * ERNs come in
			 */
			orl_empty = 1;
		}
		/*
		 * Retirement succeeded, check to see if FQ needs
		 * to be drained
		 */
		if (drain || mcr->alterfq.fqs & QM_MCR_FQS_NOTEMPTY) {
			/* FQ is Not Empty, drain using volatile DQ commands */
			do {
				u32 vdqcr = fqid | QM_VDQCR_NUMFRAMES_SET(3);

				qm_dqrr_vdqcr_set(&p->p, vdqcr);
				/*
				 * Wait for a dequeue and process the dequeues,
				 * making sure to empty the ring completely
				 */
			} while (!qm_dqrr_drain_wait(&p->p, fqid, FQ_EMPTY));
		}

		while (!orl_empty) {
			/* Wait for the ORL to have been completely drained */
			orl_empty = qm_mr_drain(&p->p, FQRL);
			cpu_relax();
		}
		mcc = qm_mc_start(&p->p);
		qm_fqid_set(&mcc->fq, fqid);
		qm_mc_commit(&p->p, QM_MCC_VERB_ALTER_OOS);
		if (!qm_mc_result_timeout(&p->p, &mcr)) {
			ret = -ETIMEDOUT;
			goto out;
		}

		DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) ==
			    QM_MCR_VERB_ALTER_OOS);
		if (mcr->result != QM_MCR_RESULT_OK) {
			dev_err(dev, "OOS after drain fail: FQ 0x%x (0x%x)\n",
				fqid, mcr->result);
			ret = -EIO;
			goto out;
		}
		break;

	case QM_MCR_NP_STATE_RETIRED:
		/* Send OOS Command */
		mcc = qm_mc_start(&p->p);
		qm_fqid_set(&mcc->fq, fqid);
		qm_mc_commit(&p->p, QM_MCC_VERB_ALTER_OOS);
		if (!qm_mc_result_timeout(&p->p, &mcr)) {
			ret = -ETIMEDOUT;
			goto out;
		}

		DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) ==
			    QM_MCR_VERB_ALTER_OOS);
		if (mcr->result != QM_MCR_RESULT_OK) {
			dev_err(dev, "OOS fail: FQ 0x%x (0x%x)\n",
				fqid, mcr->result);
			ret = -EIO;
			goto out;
		}
		break;

	case QM_MCR_NP_STATE_OOS:
		/*  Done */
		break;

	default:
		ret = -EIO;
	}

out:
	put_affine_portal();
	return ret;
}