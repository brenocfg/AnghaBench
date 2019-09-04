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
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
typedef  enum qed_ov_eswitch { ____Placeholder_qed_ov_eswitch } qed_ov_eswitch ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DRV_MB_PARAM_ESWITCH_MODE_NONE ; 
 int /*<<< orphan*/  DRV_MB_PARAM_ESWITCH_MODE_VEB ; 
 int /*<<< orphan*/  DRV_MB_PARAM_ESWITCH_MODE_VEPA ; 
 int /*<<< orphan*/  DRV_MSG_CODE_OV_UPDATE_ESWITCH_MODE ; 
 int EINVAL ; 
#define  QED_OV_ESWITCH_NONE 130 
#define  QED_OV_ESWITCH_VEB 129 
#define  QED_OV_ESWITCH_VEPA 128 
 int qed_mcp_cmd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int qed_mcp_ov_update_eswitch(struct qed_hwfn *p_hwfn,
			      struct qed_ptt *p_ptt,
			      enum qed_ov_eswitch eswitch)
{
	u32 resp = 0, param = 0;
	u32 drv_mb_param;
	int rc;

	switch (eswitch) {
	case QED_OV_ESWITCH_NONE:
		drv_mb_param = DRV_MB_PARAM_ESWITCH_MODE_NONE;
		break;
	case QED_OV_ESWITCH_VEB:
		drv_mb_param = DRV_MB_PARAM_ESWITCH_MODE_VEB;
		break;
	case QED_OV_ESWITCH_VEPA:
		drv_mb_param = DRV_MB_PARAM_ESWITCH_MODE_VEPA;
		break;
	default:
		DP_ERR(p_hwfn, "Invalid eswitch mode %d\n", eswitch);
		return -EINVAL;
	}

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_OV_UPDATE_ESWITCH_MODE,
			 drv_mb_param, &resp, &param);
	if (rc)
		DP_ERR(p_hwfn, "Failed to send eswitch mode, rc = %d\n", rc);

	return rc;
}