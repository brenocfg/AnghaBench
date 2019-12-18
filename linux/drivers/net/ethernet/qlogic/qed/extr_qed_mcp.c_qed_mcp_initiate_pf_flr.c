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
 int /*<<< orphan*/  DRV_MSG_CODE_INITIATE_PF_FLR ; 
 int qed_mcp_cmd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int qed_mcp_initiate_pf_flr(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	u32 mcp_resp, mcp_param;

	return qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_INITIATE_PF_FLR, 0,
			   &mcp_resp, &mcp_param);
}