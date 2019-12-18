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
struct qed_resc_unlock_params {int resource; int b_released; scalar_t__ b_force; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct qed_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,...) ; 
 int EINVAL ; 
 int QED_MFW_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QED_MFW_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  QED_MSG_SP ; 
 int /*<<< orphan*/  RESOURCE_CMD_REQ_OPCODE ; 
 int /*<<< orphan*/  RESOURCE_CMD_REQ_RESC ; 
 int /*<<< orphan*/  RESOURCE_CMD_RSP_OPCODE ; 
 int RESOURCE_OPCODE_FORCE_RELEASE ; 
 int RESOURCE_OPCODE_RELEASE ; 
#define  RESOURCE_OPCODE_RELEASED 130 
#define  RESOURCE_OPCODE_RELEASED_PREVIOUS 129 
#define  RESOURCE_OPCODE_WRONG_OWNER 128 
 int qed_mcp_resource_cmd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
qed_mcp_resc_unlock(struct qed_hwfn *p_hwfn,
		    struct qed_ptt *p_ptt,
		    struct qed_resc_unlock_params *p_params)
{
	u32 param = 0, mcp_resp, mcp_param;
	u8 opcode;
	int rc;

	opcode = p_params->b_force ? RESOURCE_OPCODE_FORCE_RELEASE
				   : RESOURCE_OPCODE_RELEASE;
	QED_MFW_SET_FIELD(param, RESOURCE_CMD_REQ_RESC, p_params->resource);
	QED_MFW_SET_FIELD(param, RESOURCE_CMD_REQ_OPCODE, opcode);

	DP_VERBOSE(p_hwfn, QED_MSG_SP,
		   "Resource unlock request: param 0x%08x [opcode %d, resource %d]\n",
		   param, opcode, p_params->resource);

	/* Attempt to release the resource */
	rc = qed_mcp_resource_cmd(p_hwfn, p_ptt, param, &mcp_resp, &mcp_param);
	if (rc)
		return rc;

	/* Analyze the response */
	opcode = QED_MFW_GET_FIELD(mcp_param, RESOURCE_CMD_RSP_OPCODE);

	DP_VERBOSE(p_hwfn, QED_MSG_SP,
		   "Resource unlock response: mcp_param 0x%08x [opcode %d]\n",
		   mcp_param, opcode);

	switch (opcode) {
	case RESOURCE_OPCODE_RELEASED_PREVIOUS:
		DP_INFO(p_hwfn,
			"Resource unlock request for an already released resource [%d]\n",
			p_params->resource);
		/* Fallthrough */
	case RESOURCE_OPCODE_RELEASED:
		p_params->b_released = true;
		break;
	case RESOURCE_OPCODE_WRONG_OWNER:
		p_params->b_released = false;
		break;
	default:
		DP_NOTICE(p_hwfn,
			  "Unexpected opcode in resource unlock response [mcp_param 0x%08x, opcode %d]\n",
			  mcp_param, opcode);
		return -EINVAL;
	}

	return 0;
}