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
typedef  void* u32 ;
struct qed_ptt {int dummy; } ;
struct qed_mcp_mb_params {void* mcp_param; void* mcp_resp; void* param; void* cmd; } ;
struct qed_hwfn {int dummy; } ;
typedef  int /*<<< orphan*/  mb_params ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct qed_mcp_mb_params*,int /*<<< orphan*/ ,int) ; 
 int qed_mcp_cmd_and_union (struct qed_hwfn*,struct qed_ptt*,struct qed_mcp_mb_params*) ; 

int qed_mcp_cmd(struct qed_hwfn *p_hwfn,
		struct qed_ptt *p_ptt,
		u32 cmd,
		u32 param,
		u32 *o_mcp_resp,
		u32 *o_mcp_param)
{
	struct qed_mcp_mb_params mb_params;
	int rc;

	memset(&mb_params, 0, sizeof(mb_params));
	mb_params.cmd = cmd;
	mb_params.param = param;

	rc = qed_mcp_cmd_and_union(p_hwfn, p_ptt, &mb_params);
	if (rc)
		return rc;

	*o_mcp_resp = mb_params.mcp_resp;
	*o_mcp_param = mb_params.mcp_param;

	return 0;
}