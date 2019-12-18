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
typedef  enum qed_led_mode { ____Placeholder_qed_led_mode } qed_led_mode ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DRV_MB_PARAM_SET_LED_MODE_OFF ; 
 int /*<<< orphan*/  DRV_MB_PARAM_SET_LED_MODE_ON ; 
 int /*<<< orphan*/  DRV_MB_PARAM_SET_LED_MODE_OPER ; 
 int /*<<< orphan*/  DRV_MSG_CODE_SET_LED_MODE ; 
 int EINVAL ; 
#define  QED_LED_MODE_OFF 130 
#define  QED_LED_MODE_ON 129 
#define  QED_LED_MODE_RESTORE 128 
 int qed_mcp_cmd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int qed_mcp_set_led(struct qed_hwfn *p_hwfn,
		    struct qed_ptt *p_ptt, enum qed_led_mode mode)
{
	u32 resp = 0, param = 0, drv_mb_param;
	int rc;

	switch (mode) {
	case QED_LED_MODE_ON:
		drv_mb_param = DRV_MB_PARAM_SET_LED_MODE_ON;
		break;
	case QED_LED_MODE_OFF:
		drv_mb_param = DRV_MB_PARAM_SET_LED_MODE_OFF;
		break;
	case QED_LED_MODE_RESTORE:
		drv_mb_param = DRV_MB_PARAM_SET_LED_MODE_OPER;
		break;
	default:
		DP_NOTICE(p_hwfn, "Invalid LED mode %d\n", mode);
		return -EINVAL;
	}

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_SET_LED_MODE,
			 drv_mb_param, &resp, &param);

	return rc;
}