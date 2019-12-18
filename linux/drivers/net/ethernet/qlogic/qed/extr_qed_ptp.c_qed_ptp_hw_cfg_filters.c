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
struct qed_ptt {int dummy; } ;
struct qed_hwfn {struct qed_ptt* p_ptp_ptt; } ;
struct qed_dev {int dummy; } ;
typedef  enum qed_ptp_hwtstamp_tx_type { ____Placeholder_qed_ptp_hwtstamp_tx_type } qed_ptp_hwtstamp_tx_type ;
typedef  enum qed_ptp_filter_type { ____Placeholder_qed_ptp_filter_type } qed_ptp_filter_type ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qed_hwfn*,char*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NIG_REG_LLH_PTP_HOST_BUF_SEQID ; 
 int /*<<< orphan*/  NIG_REG_LLH_PTP_PARAM_MASK ; 
 int /*<<< orphan*/  NIG_REG_LLH_PTP_RULE_MASK ; 
 int /*<<< orphan*/  NIG_REG_RX_PTP_EN ; 
 int /*<<< orphan*/  NIG_REG_TX_LLH_PTP_PARAM_MASK ; 
 int /*<<< orphan*/  NIG_REG_TX_LLH_PTP_RULE_MASK ; 
 int /*<<< orphan*/  NIG_REG_TX_PTP_EN ; 
 struct qed_hwfn* QED_LEADING_HWFN (struct qed_dev*) ; 
#define  QED_PTP_FILTER_ALL 137 
#define  QED_PTP_FILTER_NONE 136 
#define  QED_PTP_FILTER_V1_L4_EVENT 135 
#define  QED_PTP_FILTER_V1_L4_GEN 134 
#define  QED_PTP_FILTER_V2_EVENT 133 
#define  QED_PTP_FILTER_V2_GEN 132 
#define  QED_PTP_FILTER_V2_L2_EVENT 131 
#define  QED_PTP_FILTER_V2_L2_GEN 130 
#define  QED_PTP_FILTER_V2_L4_EVENT 129 
#define  QED_PTP_FILTER_V2_L4_GEN 128 
 int QED_PTP_HWTSTAMP_TX_OFF ; 
 int QED_PTP_UCAST_PARAM_MASK ; 
 int QED_TIMESTAMP_MASK ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qed_ptp_hw_cfg_filters(struct qed_dev *cdev,
				  enum qed_ptp_filter_type rx_type,
				  enum qed_ptp_hwtstamp_tx_type tx_type)
{
	struct qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	struct qed_ptt *p_ptt = p_hwfn->p_ptp_ptt;
	u32 rule_mask, enable_cfg = 0x0;

	switch (rx_type) {
	case QED_PTP_FILTER_NONE:
		enable_cfg = 0x0;
		rule_mask = 0x3FFF;
		break;
	case QED_PTP_FILTER_ALL:
		enable_cfg = 0x7;
		rule_mask = 0x3CAA;
		break;
	case QED_PTP_FILTER_V1_L4_EVENT:
		enable_cfg = 0x3;
		rule_mask = 0x3FFA;
		break;
	case QED_PTP_FILTER_V1_L4_GEN:
		enable_cfg = 0x3;
		rule_mask = 0x3FFE;
		break;
	case QED_PTP_FILTER_V2_L4_EVENT:
		enable_cfg = 0x5;
		rule_mask = 0x3FAA;
		break;
	case QED_PTP_FILTER_V2_L4_GEN:
		enable_cfg = 0x5;
		rule_mask = 0x3FEE;
		break;
	case QED_PTP_FILTER_V2_L2_EVENT:
		enable_cfg = 0x5;
		rule_mask = 0x3CFF;
		break;
	case QED_PTP_FILTER_V2_L2_GEN:
		enable_cfg = 0x5;
		rule_mask = 0x3EFF;
		break;
	case QED_PTP_FILTER_V2_EVENT:
		enable_cfg = 0x5;
		rule_mask = 0x3CAA;
		break;
	case QED_PTP_FILTER_V2_GEN:
		enable_cfg = 0x5;
		rule_mask = 0x3EEE;
		break;
	default:
		DP_INFO(p_hwfn, "Invalid PTP filter type %d\n", rx_type);
		return -EINVAL;
	}

	qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_PTP_PARAM_MASK,
	       QED_PTP_UCAST_PARAM_MASK);
	qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_PTP_RULE_MASK, rule_mask);
	qed_wr(p_hwfn, p_ptt, NIG_REG_RX_PTP_EN, enable_cfg);

	if (tx_type == QED_PTP_HWTSTAMP_TX_OFF) {
		qed_wr(p_hwfn, p_ptt, NIG_REG_TX_PTP_EN, 0x0);
		qed_wr(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_PARAM_MASK, 0x7FF);
		qed_wr(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_RULE_MASK, 0x3FFF);
	} else {
		qed_wr(p_hwfn, p_ptt, NIG_REG_TX_PTP_EN, enable_cfg);
		qed_wr(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_PARAM_MASK,
		       QED_PTP_UCAST_PARAM_MASK);
		qed_wr(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_RULE_MASK, rule_mask);
	}

	/* Reset possibly old timestamps */
	qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_PTP_HOST_BUF_SEQID,
	       QED_TIMESTAMP_MASK);

	return 0;
}