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
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; struct qed_ptt* p_ptp_ptt; } ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int EBUSY ; 
 int /*<<< orphan*/  NIG_REG_LLH_PTP_HOST_BUF_SEQID ; 
 int /*<<< orphan*/  NIG_REG_LLH_PTP_PARAM_MASK ; 
 int /*<<< orphan*/  NIG_REG_LLH_PTP_RULE_MASK ; 
 int /*<<< orphan*/  NIG_REG_PTP_LATCH_OSTS_PKT_TIME ; 
 int /*<<< orphan*/  NIG_REG_RX_PTP_EN ; 
 int /*<<< orphan*/  NIG_REG_TIMESYNC_GEN_REG_BB ; 
 int /*<<< orphan*/  NIG_REG_TSGEN_DRIFT_CNTR_CONF ; 
 int /*<<< orphan*/  NIG_REG_TSGEN_FREECNT_UPDATE_K2 ; 
 int /*<<< orphan*/  NIG_REG_TSGEN_FREE_CNT_VALUE_LSB ; 
 int /*<<< orphan*/  NIG_REG_TSGEN_FREE_CNT_VALUE_MSB ; 
 int /*<<< orphan*/  NIG_REG_TSGEN_RST_DRIFT_CNTR ; 
 int /*<<< orphan*/  NIG_REG_TS_OUTPUT_ENABLE_PDA ; 
 int /*<<< orphan*/  NIG_REG_TX_LLH_PTP_BUF_SEQID ; 
 int /*<<< orphan*/  NIG_REG_TX_LLH_PTP_PARAM_MASK ; 
 int /*<<< orphan*/  NIG_REG_TX_LLH_PTP_RULE_MASK ; 
 int /*<<< orphan*/  NIG_REG_TX_PTP_EN ; 
 scalar_t__ QED_IS_AH (int /*<<< orphan*/ ) ; 
 scalar_t__ QED_IS_BB_B0 (int /*<<< orphan*/ ) ; 
 struct qed_hwfn* QED_LEADING_HWFN (struct qed_dev*) ; 
 int QED_TIMESTAMP_MASK ; 
 int qed_ptp_res_lock (struct qed_hwfn*,struct qed_ptt*) ; 
 struct qed_ptt* qed_ptt_acquire (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_ptt_release (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qed_ptp_hw_enable(struct qed_dev *cdev)
{
	struct qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	struct qed_ptt *p_ptt;
	int rc;

	p_ptt = qed_ptt_acquire(p_hwfn);
	if (!p_ptt) {
		DP_NOTICE(p_hwfn, "Failed to acquire PTT for PTP\n");
		return -EBUSY;
	}

	p_hwfn->p_ptp_ptt = p_ptt;

	rc = qed_ptp_res_lock(p_hwfn, p_ptt);
	if (rc) {
		DP_INFO(p_hwfn,
			"Couldn't acquire the resource lock, skip ptp enable for this PF\n");
		qed_ptt_release(p_hwfn, p_ptt);
		p_hwfn->p_ptp_ptt = NULL;
		return rc;
	}

	/* Reset PTP event detection rules - will be configured in the IOCTL */
	qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_PTP_PARAM_MASK, 0x7FF);
	qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_PTP_RULE_MASK, 0x3FFF);
	qed_wr(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_PARAM_MASK, 0x7FF);
	qed_wr(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_RULE_MASK, 0x3FFF);

	qed_wr(p_hwfn, p_ptt, NIG_REG_TX_PTP_EN, 7);
	qed_wr(p_hwfn, p_ptt, NIG_REG_RX_PTP_EN, 7);

	qed_wr(p_hwfn, p_ptt, NIG_REG_TS_OUTPUT_ENABLE_PDA, 0x1);

	/* Pause free running counter */
	if (QED_IS_BB_B0(p_hwfn->cdev))
		qed_wr(p_hwfn, p_ptt, NIG_REG_TIMESYNC_GEN_REG_BB, 2);
	if (QED_IS_AH(p_hwfn->cdev))
		qed_wr(p_hwfn, p_ptt, NIG_REG_TSGEN_FREECNT_UPDATE_K2, 2);

	qed_wr(p_hwfn, p_ptt, NIG_REG_TSGEN_FREE_CNT_VALUE_LSB, 0);
	qed_wr(p_hwfn, p_ptt, NIG_REG_TSGEN_FREE_CNT_VALUE_MSB, 0);
	/* Resume free running counter */
	if (QED_IS_BB_B0(p_hwfn->cdev))
		qed_wr(p_hwfn, p_ptt, NIG_REG_TIMESYNC_GEN_REG_BB, 4);
	if (QED_IS_AH(p_hwfn->cdev)) {
		qed_wr(p_hwfn, p_ptt, NIG_REG_TSGEN_FREECNT_UPDATE_K2, 4);
		qed_wr(p_hwfn, p_ptt, NIG_REG_PTP_LATCH_OSTS_PKT_TIME, 1);
	}

	/* Disable drift register */
	qed_wr(p_hwfn, p_ptt, NIG_REG_TSGEN_DRIFT_CNTR_CONF, 0x0);
	qed_wr(p_hwfn, p_ptt, NIG_REG_TSGEN_RST_DRIFT_CNTR, 0x0);

	/* Reset possibly old timestamps */
	qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_PTP_HOST_BUF_SEQID,
	       QED_TIMESTAMP_MASK);
	qed_wr(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_BUF_SEQID, QED_TIMESTAMP_MASK);

	return 0;
}