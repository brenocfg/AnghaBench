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
struct qed_mcp_mb_params {int data_src_size; struct qed_mcp_mb_params* p_data_src; int /*<<< orphan*/  cmd; int /*<<< orphan*/ * name; int /*<<< orphan*/  version; } ;
struct qed_mcp_drv_version {int /*<<< orphan*/ * name; int /*<<< orphan*/  version; } ;
struct qed_hwfn {int dummy; } ;
struct drv_version_stc {int data_src_size; struct drv_version_stc* p_data_src; int /*<<< orphan*/  cmd; int /*<<< orphan*/ * name; int /*<<< orphan*/  version; } ;
typedef  int /*<<< orphan*/  mb_params ;
typedef  int /*<<< orphan*/  drv_version ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_SET_VERSION ; 
 int MCP_DRV_VER_STR_SIZE ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct qed_mcp_mb_params*,int /*<<< orphan*/ ,int) ; 
 int qed_mcp_cmd_and_union (struct qed_hwfn*,struct qed_ptt*,struct qed_mcp_mb_params*) ; 

int
qed_mcp_send_drv_version(struct qed_hwfn *p_hwfn,
			 struct qed_ptt *p_ptt,
			 struct qed_mcp_drv_version *p_ver)
{
	struct qed_mcp_mb_params mb_params;
	struct drv_version_stc drv_version;
	__be32 val;
	u32 i;
	int rc;

	memset(&drv_version, 0, sizeof(drv_version));
	drv_version.version = p_ver->version;
	for (i = 0; i < (MCP_DRV_VER_STR_SIZE - 4) / sizeof(u32); i++) {
		val = cpu_to_be32(*((u32 *)&p_ver->name[i * sizeof(u32)]));
		*(__be32 *)&drv_version.name[i * sizeof(u32)] = val;
	}

	memset(&mb_params, 0, sizeof(mb_params));
	mb_params.cmd = DRV_MSG_CODE_SET_VERSION;
	mb_params.p_data_src = &drv_version;
	mb_params.data_src_size = sizeof(drv_version);
	rc = qed_mcp_cmd_and_union(p_hwfn, p_ptt, &mb_params);
	if (rc)
		DP_ERR(p_hwfn, "MCP response failure, aborting\n");

	return rc;
}