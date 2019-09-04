#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct qed_ptt {int dummy; } ;
struct TYPE_4__ {scalar_t__ b_wol_support; } ;
struct qed_hwfn {TYPE_1__* cdev; TYPE_2__ hw_info; } ;
typedef  enum qed_ov_wol { ____Placeholder_qed_ov_wol } qed_ov_wol ;
struct TYPE_3__ {scalar_t__ wol_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DRV_MB_PARAM_WOL_DEFAULT ; 
 int /*<<< orphan*/  DRV_MB_PARAM_WOL_DISABLED ; 
 int /*<<< orphan*/  DRV_MB_PARAM_WOL_ENABLED ; 
 int /*<<< orphan*/  DRV_MSG_CODE_OV_UPDATE_WOL ; 
 int EINVAL ; 
 int /*<<< orphan*/  QED_MSG_SP ; 
#define  QED_OV_WOL_DEFAULT 130 
#define  QED_OV_WOL_DISABLED 129 
#define  QED_OV_WOL_ENABLED 128 
 scalar_t__ QED_WOL_SUPPORT_NONE ; 
 int qed_mcp_cmd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int qed_mcp_ov_update_wol(struct qed_hwfn *p_hwfn,
			  struct qed_ptt *p_ptt, enum qed_ov_wol wol)
{
	u32 resp = 0, param = 0;
	u32 drv_mb_param;
	int rc;

	if (p_hwfn->hw_info.b_wol_support == QED_WOL_SUPPORT_NONE) {
		DP_VERBOSE(p_hwfn, QED_MSG_SP,
			   "Can't change WoL configuration when WoL isn't supported\n");
		return -EINVAL;
	}

	switch (wol) {
	case QED_OV_WOL_DEFAULT:
		drv_mb_param = DRV_MB_PARAM_WOL_DEFAULT;
		break;
	case QED_OV_WOL_DISABLED:
		drv_mb_param = DRV_MB_PARAM_WOL_DISABLED;
		break;
	case QED_OV_WOL_ENABLED:
		drv_mb_param = DRV_MB_PARAM_WOL_ENABLED;
		break;
	default:
		DP_ERR(p_hwfn, "Invalid wol state %d\n", wol);
		return -EINVAL;
	}

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_OV_UPDATE_WOL,
			 drv_mb_param, &resp, &param);
	if (rc)
		DP_ERR(p_hwfn, "Failed to send wol mode, rc = %d\n", rc);

	/* Store the WoL update for a future unload */
	p_hwfn->cdev->wol_config = (u8)wol;

	return rc;
}