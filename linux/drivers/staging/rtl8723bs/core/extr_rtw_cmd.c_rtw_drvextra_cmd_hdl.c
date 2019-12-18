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
struct sta_info {int dummy; } ;
struct drvextra_cmd_parm {int ec_id; scalar_t__ size; scalar_t__ pbuf; int /*<<< orphan*/  type; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
#define  BTINFO_WK_CID 138 
#define  C2H_WK_CID 137 
#define  CHECK_HIQ_WK_CID 136 
#define  DM_IN_LPS_WK_CID 135 
#define  DM_RA_MSK_WK_CID 134 
#define  DYNAMIC_CHK_WK_CID 133 
#define  FREE_ASSOC_RESOURCES 132 
 int /*<<< orphan*/  H2C_PARAMETERS_ERROR ; 
 int /*<<< orphan*/  H2C_SUCCESS ; 
 int /*<<< orphan*/  HW_VAR_C2H_HANDLE ; 
#define  LPS_CHANGE_DTIM_CID 131 
#define  LPS_CTRL_WK_CID 130 
#define  POWER_SAVING_CTRL_WK_CID 129 
#define  RESET_SECURITYPRIV 128 
 int /*<<< orphan*/  dynamic_chk_wk_hdl (struct adapter*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  lps_ctrl_wk_hdl (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_btinfo_hdl (struct adapter*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rtw_chk_hi_queue_hdl (struct adapter*) ; 
 int /*<<< orphan*/  rtw_dm_in_lps_hdl (struct adapter*) ; 
 int /*<<< orphan*/  rtw_dm_ra_mask_hdl (struct adapter*,struct sta_info*) ; 
 int /*<<< orphan*/  rtw_free_assoc_resources (struct adapter*,int) ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg_with_buf (struct adapter*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rtw_lps_change_dtim_hdl (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_ps_processor (struct adapter*) ; 
 int /*<<< orphan*/  rtw_reset_securitypriv (struct adapter*) ; 

u8 rtw_drvextra_cmd_hdl(struct adapter *padapter, unsigned char *pbuf)
{
	struct drvextra_cmd_parm *pdrvextra_cmd;

	if (!pbuf)
		return H2C_PARAMETERS_ERROR;

	pdrvextra_cmd = (struct drvextra_cmd_parm *)pbuf;

	switch (pdrvextra_cmd->ec_id) {
	case DYNAMIC_CHK_WK_CID:/* only  primary padapter go to this cmd, but execute dynamic_chk_wk_hdl() for two interfaces */
		dynamic_chk_wk_hdl(padapter);
		break;
	case POWER_SAVING_CTRL_WK_CID:
		rtw_ps_processor(padapter);
		break;
	case LPS_CTRL_WK_CID:
		lps_ctrl_wk_hdl(padapter, (u8)pdrvextra_cmd->type);
		break;
	case DM_IN_LPS_WK_CID:
		rtw_dm_in_lps_hdl(padapter);
		break;
	case LPS_CHANGE_DTIM_CID:
		rtw_lps_change_dtim_hdl(padapter, (u8)pdrvextra_cmd->type);
		break;
	case CHECK_HIQ_WK_CID:
		rtw_chk_hi_queue_hdl(padapter);
		break;
	/* add for CONFIG_IEEE80211W, none 11w can use it */
	case RESET_SECURITYPRIV:
		rtw_reset_securitypriv(padapter);
		break;
	case FREE_ASSOC_RESOURCES:
		rtw_free_assoc_resources(padapter, 1);
		break;
	case C2H_WK_CID:
		rtw_hal_set_hwreg_with_buf(padapter, HW_VAR_C2H_HANDLE, pdrvextra_cmd->pbuf, pdrvextra_cmd->size);
		break;
	case DM_RA_MSK_WK_CID:
		rtw_dm_ra_mask_hdl(padapter, (struct sta_info *)pdrvextra_cmd->pbuf);
		break;
	case BTINFO_WK_CID:
		rtw_btinfo_hdl(padapter, pdrvextra_cmd->pbuf, pdrvextra_cmd->size);
		break;
	default:
		break;
	}

	if (pdrvextra_cmd->pbuf && pdrvextra_cmd->size > 0) {
		kfree(pdrvextra_cmd->pbuf);
	}

	return H2C_SUCCESS;
}