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
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int DRV_MB_PARAM_FEATURE_SUPPORT_FUNC_VLINK ; 
 int DRV_MB_PARAM_FEATURE_SUPPORT_PORT_EEE ; 
 int /*<<< orphan*/  DRV_MSG_CODE_FEATURE_SUPPORT ; 
 int qed_mcp_cmd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int,int*,int*) ; 

int qed_mcp_set_capabilities(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	u32 mcp_resp, mcp_param, features;

	features = DRV_MB_PARAM_FEATURE_SUPPORT_PORT_EEE |
		   DRV_MB_PARAM_FEATURE_SUPPORT_FUNC_VLINK;

	return qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_FEATURE_SUPPORT,
			   features, &mcp_resp, &mcp_param);
}