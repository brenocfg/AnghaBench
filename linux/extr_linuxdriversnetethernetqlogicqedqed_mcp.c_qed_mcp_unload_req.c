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
struct qed_mcp_mb_params {int flags; int /*<<< orphan*/  param; int /*<<< orphan*/  cmd; } ;
struct qed_hwfn {TYPE_1__* cdev; } ;
typedef  int /*<<< orphan*/  mb_params ;
struct TYPE_2__ {int wol_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DRV_MB_PARAM_UNLOAD_WOL_DISABLED ; 
 int /*<<< orphan*/  DRV_MB_PARAM_UNLOAD_WOL_ENABLED ; 
 int /*<<< orphan*/  DRV_MB_PARAM_UNLOAD_WOL_MCP ; 
 int /*<<< orphan*/  DRV_MSG_CODE_UNLOAD_REQ ; 
 int QED_MB_FLAG_AVOID_BLOCK ; 
 int QED_MB_FLAG_CAN_SLEEP ; 
#define  QED_OV_WOL_DEFAULT 130 
#define  QED_OV_WOL_DISABLED 129 
#define  QED_OV_WOL_ENABLED 128 
 int /*<<< orphan*/  memset (struct qed_mcp_mb_params*,int /*<<< orphan*/ ,int) ; 
 int qed_mcp_cmd_and_union (struct qed_hwfn*,struct qed_ptt*,struct qed_mcp_mb_params*) ; 

int qed_mcp_unload_req(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	struct qed_mcp_mb_params mb_params;
	u32 wol_param;

	switch (p_hwfn->cdev->wol_config) {
	case QED_OV_WOL_DISABLED:
		wol_param = DRV_MB_PARAM_UNLOAD_WOL_DISABLED;
		break;
	case QED_OV_WOL_ENABLED:
		wol_param = DRV_MB_PARAM_UNLOAD_WOL_ENABLED;
		break;
	default:
		DP_NOTICE(p_hwfn,
			  "Unknown WoL configuration %02x\n",
			  p_hwfn->cdev->wol_config);
		/* Fallthrough */
	case QED_OV_WOL_DEFAULT:
		wol_param = DRV_MB_PARAM_UNLOAD_WOL_MCP;
	}

	memset(&mb_params, 0, sizeof(mb_params));
	mb_params.cmd = DRV_MSG_CODE_UNLOAD_REQ;
	mb_params.param = wol_param;
	mb_params.flags = QED_MB_FLAG_CAN_SLEEP | QED_MB_FLAG_AVOID_BLOCK;

	return qed_mcp_cmd_and_union(p_hwfn, p_ptt, &mb_params);
}