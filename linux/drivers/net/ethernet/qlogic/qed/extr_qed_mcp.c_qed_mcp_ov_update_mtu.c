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
typedef  scalar_t__ u16 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,int) ; 
 int DRV_MB_PARAM_OV_MTU_SIZE_SHIFT ; 
 int /*<<< orphan*/  DRV_MSG_CODE_OV_UPDATE_MTU ; 
 int qed_mcp_cmd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int,int*,int*) ; 

int qed_mcp_ov_update_mtu(struct qed_hwfn *p_hwfn,
			  struct qed_ptt *p_ptt, u16 mtu)
{
	u32 resp = 0, param = 0;
	u32 drv_mb_param;
	int rc;

	drv_mb_param = (u32)mtu << DRV_MB_PARAM_OV_MTU_SIZE_SHIFT;
	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_OV_UPDATE_MTU,
			 drv_mb_param, &resp, &param);
	if (rc)
		DP_ERR(p_hwfn, "Failed to send mtu value, rc = %d\n", rc);

	return rc;
}