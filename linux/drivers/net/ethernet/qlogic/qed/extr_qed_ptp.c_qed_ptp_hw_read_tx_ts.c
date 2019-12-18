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
typedef  int u64 ;
typedef  int u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {struct qed_ptt* p_ptp_ptt; } ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NIG_REG_TX_LLH_PTP_BUF_SEQID ; 
 int /*<<< orphan*/  NIG_REG_TX_LLH_PTP_BUF_TS_LSB ; 
 int /*<<< orphan*/  NIG_REG_TX_LLH_PTP_BUF_TS_MSB ; 
 struct qed_hwfn* QED_LEADING_HWFN (struct qed_dev*) ; 
 int /*<<< orphan*/  QED_MSG_DEBUG ; 
 int QED_TIMESTAMP_MASK ; 
 int qed_rd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qed_ptp_hw_read_tx_ts(struct qed_dev *cdev, u64 *timestamp)
{
	struct qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	struct qed_ptt *p_ptt = p_hwfn->p_ptp_ptt;
	u32 val;

	*timestamp = 0;
	val = qed_rd(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_BUF_SEQID);
	if (!(val & QED_TIMESTAMP_MASK)) {
		DP_VERBOSE(p_hwfn, QED_MSG_DEBUG,
			   "Invalid Tx timestamp, buf_seqid = %08x\n", val);
		return -EINVAL;
	}

	val = qed_rd(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_BUF_TS_LSB);
	*timestamp = qed_rd(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_BUF_TS_MSB);
	*timestamp <<= 32;
	*timestamp |= val;

	/* Reset timestamp register to allow new timestamp */
	qed_wr(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_BUF_SEQID, QED_TIMESTAMP_MASK);

	return 0;
}