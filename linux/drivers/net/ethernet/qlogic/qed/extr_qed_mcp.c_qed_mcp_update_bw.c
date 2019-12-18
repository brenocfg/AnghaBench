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
struct qed_mcp_function_info {int /*<<< orphan*/  bandwidth_max; int /*<<< orphan*/  bandwidth_min; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; TYPE_1__* mcp_info; } ;
struct public_func {int dummy; } ;
struct TYPE_2__ {struct qed_mcp_function_info func_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_MSG_CODE_BW_UPDATE_ACK ; 
 int /*<<< orphan*/  MCP_PF_ID (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_configure_pf_max_bandwidth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_configure_pf_min_bandwidth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_mcp_cmd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_mcp_get_shmem_func (struct qed_hwfn*,struct qed_ptt*,struct public_func*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_read_pf_bandwidth (struct qed_hwfn*,struct public_func*) ; 

__attribute__((used)) static void qed_mcp_update_bw(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	struct qed_mcp_function_info *p_info;
	struct public_func shmem_info;
	u32 resp = 0, param = 0;

	qed_mcp_get_shmem_func(p_hwfn, p_ptt, &shmem_info, MCP_PF_ID(p_hwfn));

	qed_read_pf_bandwidth(p_hwfn, &shmem_info);

	p_info = &p_hwfn->mcp_info->func_info;

	qed_configure_pf_min_bandwidth(p_hwfn->cdev, p_info->bandwidth_min);
	qed_configure_pf_max_bandwidth(p_hwfn->cdev, p_info->bandwidth_max);

	/* Acknowledge the MFW */
	qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_BW_UPDATE_ACK, 0, &resp,
		    &param);
}