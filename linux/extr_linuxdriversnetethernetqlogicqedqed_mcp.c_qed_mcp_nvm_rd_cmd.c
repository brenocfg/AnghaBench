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
typedef  void* u32 ;
struct qed_ptt {int dummy; } ;
struct qed_mcp_mb_params {int data_dst_size; void* mcp_param; void* mcp_resp; int /*<<< orphan*/ * p_data_dst; void* param; void* cmd; } ;
struct qed_hwfn {int dummy; } ;
typedef  int /*<<< orphan*/  mb_params ;

/* Variables and functions */
 int MCP_DRV_NVM_BUF_LEN ; 
 int /*<<< orphan*/  memcpy (void**,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  memset (struct qed_mcp_mb_params*,int /*<<< orphan*/ ,int) ; 
 int qed_mcp_cmd_and_union (struct qed_hwfn*,struct qed_ptt*,struct qed_mcp_mb_params*) ; 

int qed_mcp_nvm_rd_cmd(struct qed_hwfn *p_hwfn,
		       struct qed_ptt *p_ptt,
		       u32 cmd,
		       u32 param,
		       u32 *o_mcp_resp,
		       u32 *o_mcp_param, u32 *o_txn_size, u32 *o_buf)
{
	struct qed_mcp_mb_params mb_params;
	u8 raw_data[MCP_DRV_NVM_BUF_LEN];
	int rc;

	memset(&mb_params, 0, sizeof(mb_params));
	mb_params.cmd = cmd;
	mb_params.param = param;
	mb_params.p_data_dst = raw_data;

	/* Use the maximal value since the actual one is part of the response */
	mb_params.data_dst_size = MCP_DRV_NVM_BUF_LEN;

	rc = qed_mcp_cmd_and_union(p_hwfn, p_ptt, &mb_params);
	if (rc)
		return rc;

	*o_mcp_resp = mb_params.mcp_resp;
	*o_mcp_param = mb_params.mcp_param;

	*o_txn_size = *o_mcp_param;
	memcpy(o_buf, raw_data, *o_txn_size);

	return 0;
}