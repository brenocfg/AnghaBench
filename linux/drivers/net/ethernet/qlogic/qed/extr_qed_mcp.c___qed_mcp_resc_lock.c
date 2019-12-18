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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct qed_resc_lock_params {int timeout; int resource; int b_granted; void* owner; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,...) ; 
 int EINVAL ; 
#define  QED_MCP_RESC_LOCK_TO_DEFAULT 131 
#define  QED_MCP_RESC_LOCK_TO_NONE 130 
 void* QED_MFW_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QED_MFW_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  QED_MSG_SP ; 
 int /*<<< orphan*/  RESOURCE_CMD_REQ_AGE ; 
 int /*<<< orphan*/  RESOURCE_CMD_REQ_OPCODE ; 
 int /*<<< orphan*/  RESOURCE_CMD_REQ_RESC ; 
 int /*<<< orphan*/  RESOURCE_CMD_RSP_OPCODE ; 
 int /*<<< orphan*/  RESOURCE_CMD_RSP_OWNER ; 
#define  RESOURCE_OPCODE_BUSY 129 
#define  RESOURCE_OPCODE_GNT 128 
 int RESOURCE_OPCODE_REQ ; 
 int RESOURCE_OPCODE_REQ_WO_AGING ; 
 int RESOURCE_OPCODE_REQ_W_AGING ; 
 int qed_mcp_resource_cmd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
__qed_mcp_resc_lock(struct qed_hwfn *p_hwfn,
		    struct qed_ptt *p_ptt,
		    struct qed_resc_lock_params *p_params)
{
	u32 param = 0, mcp_resp, mcp_param;
	u8 opcode;
	int rc;

	switch (p_params->timeout) {
	case QED_MCP_RESC_LOCK_TO_DEFAULT:
		opcode = RESOURCE_OPCODE_REQ;
		p_params->timeout = 0;
		break;
	case QED_MCP_RESC_LOCK_TO_NONE:
		opcode = RESOURCE_OPCODE_REQ_WO_AGING;
		p_params->timeout = 0;
		break;
	default:
		opcode = RESOURCE_OPCODE_REQ_W_AGING;
		break;
	}

	QED_MFW_SET_FIELD(param, RESOURCE_CMD_REQ_RESC, p_params->resource);
	QED_MFW_SET_FIELD(param, RESOURCE_CMD_REQ_OPCODE, opcode);
	QED_MFW_SET_FIELD(param, RESOURCE_CMD_REQ_AGE, p_params->timeout);

	DP_VERBOSE(p_hwfn,
		   QED_MSG_SP,
		   "Resource lock request: param 0x%08x [age %d, opcode %d, resource %d]\n",
		   param, p_params->timeout, opcode, p_params->resource);

	/* Attempt to acquire the resource */
	rc = qed_mcp_resource_cmd(p_hwfn, p_ptt, param, &mcp_resp, &mcp_param);
	if (rc)
		return rc;

	/* Analyze the response */
	p_params->owner = QED_MFW_GET_FIELD(mcp_param, RESOURCE_CMD_RSP_OWNER);
	opcode = QED_MFW_GET_FIELD(mcp_param, RESOURCE_CMD_RSP_OPCODE);

	DP_VERBOSE(p_hwfn,
		   QED_MSG_SP,
		   "Resource lock response: mcp_param 0x%08x [opcode %d, owner %d]\n",
		   mcp_param, opcode, p_params->owner);

	switch (opcode) {
	case RESOURCE_OPCODE_GNT:
		p_params->b_granted = true;
		break;
	case RESOURCE_OPCODE_BUSY:
		p_params->b_granted = false;
		break;
	default:
		DP_NOTICE(p_hwfn,
			  "Unexpected opcode in resource lock response [mcp_param 0x%08x, opcode %d]\n",
			  mcp_param, opcode);
		return -EINVAL;
	}

	return 0;
}