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
struct qed_resc_alloc_out_params {int res_id; int /*<<< orphan*/  mcp_resp; int /*<<< orphan*/  resc_max_val; int /*<<< orphan*/  cmd; } ;
struct qed_resc_alloc_in_params {int res_id; int /*<<< orphan*/  mcp_resp; int /*<<< orphan*/  resc_max_val; int /*<<< orphan*/  cmd; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
typedef  int /*<<< orphan*/  out_params ;
typedef  int /*<<< orphan*/  in_params ;
typedef  enum qed_resources { ____Placeholder_qed_resources } qed_resources ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_MSG_SET_RESOURCE_VALUE_MSG ; 
 int /*<<< orphan*/  memset (struct qed_resc_alloc_out_params*,int /*<<< orphan*/ ,int) ; 
 int qed_mcp_resc_allocation_msg (struct qed_hwfn*,struct qed_ptt*,struct qed_resc_alloc_out_params*,struct qed_resc_alloc_out_params*) ; 

int
qed_mcp_set_resc_max_val(struct qed_hwfn *p_hwfn,
			 struct qed_ptt *p_ptt,
			 enum qed_resources res_id,
			 u32 resc_max_val, u32 *p_mcp_resp)
{
	struct qed_resc_alloc_out_params out_params;
	struct qed_resc_alloc_in_params in_params;
	int rc;

	memset(&in_params, 0, sizeof(in_params));
	in_params.cmd = DRV_MSG_SET_RESOURCE_VALUE_MSG;
	in_params.res_id = res_id;
	in_params.resc_max_val = resc_max_val;
	memset(&out_params, 0, sizeof(out_params));
	rc = qed_mcp_resc_allocation_msg(p_hwfn, p_ptt, &in_params,
					 &out_params);
	if (rc)
		return rc;

	*p_mcp_resp = out_params.mcp_resp;

	return 0;
}