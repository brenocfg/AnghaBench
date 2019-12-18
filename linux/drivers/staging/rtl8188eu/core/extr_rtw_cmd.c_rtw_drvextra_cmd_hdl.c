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
struct drvextra_cmd_parm {int ec_id; scalar_t__ type_size; scalar_t__ pbuf; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
#define  ANT_SELECT_WK_CID 133 
#define  CHECK_HIQ_WK_CID 132 
#define  DYNAMIC_CHK_WK_CID 131 
 int /*<<< orphan*/  H2C_PARAMETERS_ERROR ; 
 int /*<<< orphan*/  H2C_SUCCESS ; 
#define  LPS_CTRL_WK_CID 130 
#define  POWER_SAVING_CTRL_WK_CID 129 
#define  RTP_TIMER_CFG_WK_CID 128 
 int /*<<< orphan*/  antenna_select_wk_hdl (struct adapter*,scalar_t__) ; 
 int /*<<< orphan*/  dynamic_chk_wk_hdl (struct adapter*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  lps_ctrl_wk_hdl (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpt_timer_setting_wk_hdl (struct adapter*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_chk_hi_queue_hdl (struct adapter*) ; 
 int /*<<< orphan*/  rtw_ps_processor (struct adapter*) ; 

u8 rtw_drvextra_cmd_hdl(struct adapter *padapter, unsigned char *pbuf)
{
	struct drvextra_cmd_parm *pdrvextra_cmd;

	if (!pbuf)
		return H2C_PARAMETERS_ERROR;

	pdrvextra_cmd = (struct drvextra_cmd_parm *)pbuf;

	switch (pdrvextra_cmd->ec_id) {
	case DYNAMIC_CHK_WK_CID:
		dynamic_chk_wk_hdl(padapter, pdrvextra_cmd->pbuf, pdrvextra_cmd->type_size);
		break;
	case POWER_SAVING_CTRL_WK_CID:
		rtw_ps_processor(padapter);
		break;
	case LPS_CTRL_WK_CID:
		lps_ctrl_wk_hdl(padapter, (u8)pdrvextra_cmd->type_size);
		break;
	case RTP_TIMER_CFG_WK_CID:
		rpt_timer_setting_wk_hdl(padapter, pdrvextra_cmd->type_size);
		break;
	case ANT_SELECT_WK_CID:
		antenna_select_wk_hdl(padapter, pdrvextra_cmd->type_size);
		break;
#ifdef CONFIG_88EU_AP_MODE
	case CHECK_HIQ_WK_CID:
		rtw_chk_hi_queue_hdl(padapter);
		break;
#endif /* CONFIG_88EU_AP_MODE */
	default:
		break;
	}

	if (pdrvextra_cmd->pbuf && pdrvextra_cmd->type_size > 0)
		kfree(pdrvextra_cmd->pbuf);

	return H2C_SUCCESS;
}