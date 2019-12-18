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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_dev*,char*,int,int) ; 
 struct qed_hwfn* QED_LEADING_HWFN (struct qed_dev*) ; 
 int QED_MAX_NVM_BUF_LEN ; 
 int /*<<< orphan*/  QED_NVM_CFG_GET_FLAGS ; 
 int qed_mcp_nvm_get_cfg (struct qed_hwfn*,struct qed_ptt*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 struct qed_ptt* qed_ptt_acquire (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_ptt_release (struct qed_hwfn*,struct qed_ptt*) ; 

__attribute__((used)) static int qed_nvm_flash_cfg_len(struct qed_dev *cdev, u32 cmd)
{
	struct qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	u8 buf[QED_MAX_NVM_BUF_LEN];
	struct qed_ptt *ptt;
	u32 len;
	int rc;

	ptt = qed_ptt_acquire(hwfn);
	if (!ptt)
		return QED_MAX_NVM_BUF_LEN;

	rc = qed_mcp_nvm_get_cfg(hwfn, ptt, cmd, 0, QED_NVM_CFG_GET_FLAGS, buf,
				 &len);
	if (rc || !len) {
		DP_ERR(cdev, "Error %d reading %d\n", rc, cmd);
		len = QED_MAX_NVM_BUF_LEN;
	}

	qed_ptt_release(hwfn, ptt);

	return len;
}