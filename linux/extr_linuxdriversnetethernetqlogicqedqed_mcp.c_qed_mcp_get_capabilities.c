#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {TYPE_1__* mcp_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_GET_MFW_FEATURE_SUPPORT ; 
 int NETIF_MSG_PROBE ; 
 int QED_MSG_SP ; 
 int qed_mcp_cmd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int qed_mcp_get_capabilities(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	u32 mcp_resp;
	int rc;

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_GET_MFW_FEATURE_SUPPORT,
			 0, &mcp_resp, &p_hwfn->mcp_info->capabilities);
	if (!rc)
		DP_VERBOSE(p_hwfn, (QED_MSG_SP | NETIF_MSG_PROBE),
			   "MFW supported features: %08x\n",
			   p_hwfn->mcp_info->capabilities);

	return rc;
}