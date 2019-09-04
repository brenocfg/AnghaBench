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
typedef  int /*<<< orphan*/  u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct qed_dev {int /*<<< orphan*/  mcp_nvm_resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_MSG_CODE_NVM_PUT_FILE_BEGIN ; 
 int EBUSY ; 
 struct qed_hwfn* QED_LEADING_HWFN (struct qed_dev*) ; 
 int qed_mcp_cmd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct qed_ptt* qed_ptt_acquire (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_ptt_release (struct qed_hwfn*,struct qed_ptt*) ; 

int qed_mcp_nvm_put_file_begin(struct qed_dev *cdev, u32 addr)
{
	struct qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	struct qed_ptt *p_ptt;
	u32 resp, param;
	int rc;

	p_ptt = qed_ptt_acquire(p_hwfn);
	if (!p_ptt)
		return -EBUSY;
	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_NVM_PUT_FILE_BEGIN, addr,
			 &resp, &param);
	cdev->mcp_nvm_resp = resp;
	qed_ptt_release(p_hwfn, p_ptt);

	return rc;
}