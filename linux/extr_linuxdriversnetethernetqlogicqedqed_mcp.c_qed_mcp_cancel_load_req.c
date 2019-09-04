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

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_CANCEL_LOAD_REQ ; 
 int qed_mcp_cmd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_mcp_cancel_load_req(struct qed_hwfn *p_hwfn,
				   struct qed_ptt *p_ptt)
{
	u32 resp = 0, param = 0;
	int rc;

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_CANCEL_LOAD_REQ, 0,
			 &resp, &param);
	if (rc)
		DP_NOTICE(p_hwfn,
			  "Failed to send cancel load request, rc = %d\n", rc);

	return rc;
}