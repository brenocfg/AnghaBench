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
typedef  scalar_t__ u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_RESOURCE_CMD ; 
 int EINVAL ; 
 scalar_t__ FW_MSG_CODE_UNSUPPORTED ; 
 int /*<<< orphan*/  QED_MFW_GET_FIELD (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESOURCE_CMD_REQ_OPCODE ; 
 scalar_t__ RESOURCE_OPCODE_UNKNOWN_CMD ; 
 int qed_mcp_cmd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int qed_mcp_resource_cmd(struct qed_hwfn *p_hwfn,
				struct qed_ptt *p_ptt,
				u32 param, u32 *p_mcp_resp, u32 *p_mcp_param)
{
	int rc;

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_RESOURCE_CMD, param,
			 p_mcp_resp, p_mcp_param);
	if (rc)
		return rc;

	if (*p_mcp_resp == FW_MSG_CODE_UNSUPPORTED) {
		DP_INFO(p_hwfn,
			"The resource command is unsupported by the MFW\n");
		return -EINVAL;
	}

	if (*p_mcp_param == RESOURCE_OPCODE_UNKNOWN_CMD) {
		u8 opcode = QED_MFW_GET_FIELD(param, RESOURCE_CMD_REQ_OPCODE);

		DP_NOTICE(p_hwfn,
			  "The resource command is unknown to the MFW [param 0x%08x, opcode %d]\n",
			  param, opcode);
		return -EINVAL;
	}

	return rc;
}