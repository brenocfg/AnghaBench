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
struct qed_mcp_mb_params {scalar_t__ mcp_resp; int /*<<< orphan*/  mcp_param; int /*<<< orphan*/  cmd; int /*<<< orphan*/  member_0; } ;
struct qed_hwfn {struct qed_dev* cdev; } ;
struct qed_dev {int /*<<< orphan*/  ppfid_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_GET_PPFID_BITMAP ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FW_MB_PARAM_PPFID_BITMAP ; 
 scalar_t__ FW_MSG_CODE_UNSUPPORTED ; 
 int /*<<< orphan*/  QED_MFW_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QED_MSG_SP ; 
 int qed_mcp_cmd_and_union (struct qed_hwfn*,struct qed_ptt*,struct qed_mcp_mb_params*) ; 

int qed_mcp_get_ppfid_bitmap(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	struct qed_mcp_mb_params mb_params = {0};
	struct qed_dev *cdev = p_hwfn->cdev;
	int rc;

	mb_params.cmd = DRV_MSG_CODE_GET_PPFID_BITMAP;
	rc = qed_mcp_cmd_and_union(p_hwfn, p_ptt, &mb_params);
	if (rc)
		return rc;

	if (mb_params.mcp_resp == FW_MSG_CODE_UNSUPPORTED) {
		DP_INFO(p_hwfn,
			"The get_ppfid_bitmap command is unsupported by the MFW\n");
		return -EOPNOTSUPP;
	}

	cdev->ppfid_bitmap = QED_MFW_GET_FIELD(mb_params.mcp_param,
					       FW_MB_PARAM_PPFID_BITMAP);

	DP_VERBOSE(p_hwfn, QED_MSG_SP, "PPFID bitmap 0x%hhx\n",
		   cdev->ppfid_bitmap);

	return 0;
}