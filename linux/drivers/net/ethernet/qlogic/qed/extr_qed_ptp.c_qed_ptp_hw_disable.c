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
struct qed_hwfn {struct qed_ptt* p_ptp_ptt; } ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIG_REG_LLH_PTP_PARAM_MASK ; 
 int /*<<< orphan*/  NIG_REG_LLH_PTP_RULE_MASK ; 
 int /*<<< orphan*/  NIG_REG_RX_PTP_EN ; 
 int /*<<< orphan*/  NIG_REG_TX_LLH_PTP_PARAM_MASK ; 
 int /*<<< orphan*/  NIG_REG_TX_LLH_PTP_RULE_MASK ; 
 int /*<<< orphan*/  NIG_REG_TX_PTP_EN ; 
 struct qed_hwfn* QED_LEADING_HWFN (struct qed_dev*) ; 
 int /*<<< orphan*/  qed_ptp_res_unlock (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_ptt_release (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qed_ptp_hw_disable(struct qed_dev *cdev)
{
	struct qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	struct qed_ptt *p_ptt = p_hwfn->p_ptp_ptt;

	qed_ptp_res_unlock(p_hwfn, p_ptt);

	/* Reset PTP event detection rules */
	qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_PTP_PARAM_MASK, 0x7FF);
	qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_PTP_RULE_MASK, 0x3FFF);

	qed_wr(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_PARAM_MASK, 0x7FF);
	qed_wr(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_RULE_MASK, 0x3FFF);

	/* Disable the PTP feature */
	qed_wr(p_hwfn, p_ptt, NIG_REG_RX_PTP_EN, 0x0);
	qed_wr(p_hwfn, p_ptt, NIG_REG_TX_PTP_EN, 0x0);

	qed_ptt_release(p_hwfn, p_ptt);
	p_hwfn->p_ptp_ptt = NULL;

	return 0;
}