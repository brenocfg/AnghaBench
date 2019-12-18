#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  size_t u32 ;
struct sitesurvey_parm {int /*<<< orphan*/  scan_mode; int /*<<< orphan*/  ch_num; int /*<<< orphan*/  ch; TYPE_1__* ssid; } ;
struct TYPE_6__ {scalar_t__ state; int /*<<< orphan*/  scan_mode; int /*<<< orphan*/  ch; int /*<<< orphan*/  ch_num; TYPE_2__* ssid; scalar_t__ channel_idx; scalar_t__ bss_cnt; } ;
struct mlme_ext_priv {TYPE_3__ sitesurvey_res; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;
struct TYPE_5__ {scalar_t__ SsidLength; int /*<<< orphan*/  Ssid; } ;
struct TYPE_4__ {scalar_t__ SsidLength; int /*<<< orphan*/  Ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DYNAMIC_FUNC_DISABLE ; 
 int H2C_SUCCESS ; 
 int /*<<< orphan*/  HW_VAR_INITIAL_GAIN ; 
 int /*<<< orphan*/  HW_VAR_MLME_SITESURVEY ; 
 int /*<<< orphan*/  IW_ESSID_MAX_SIZE ; 
 int /*<<< orphan*/  RTW_CHANNEL_SCAN_AMOUNT ; 
 size_t RTW_SSID_SCAN_AMOUNT ; 
 scalar_t__ SCAN_DISABLE ; 
 scalar_t__ SCAN_PROCESS ; 
 scalar_t__ SCAN_START ; 
 scalar_t__ SCAN_TXNULL ; 
 int /*<<< orphan*/  Save_DM_Func_Flag (struct adapter*) ; 
 int /*<<< orphan*/  Set_MSR (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Switch_DM_Func (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _HW_STATE_NOLINK_ ; 
 scalar_t__ is_client_associated_to_ap (struct adapter*) ; 
 int /*<<< orphan*/  issue_nulldata (struct adapter*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (struct adapter*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rtw_scan_ch_decision (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_survey_timer (struct mlme_ext_priv*,int) ; 
 int /*<<< orphan*/  site_survey (struct adapter*) ; 

u8 sitesurvey_cmd_hdl(struct adapter *padapter, u8 *pbuf)
{
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct sitesurvey_parm	*pparm = (struct sitesurvey_parm *)pbuf;
	u8 bdelayscan = false;
	u8 val8;
	u32 initialgain;
	u32 i;

	if (pmlmeext->sitesurvey_res.state == SCAN_DISABLE) {
		pmlmeext->sitesurvey_res.state = SCAN_START;
		pmlmeext->sitesurvey_res.bss_cnt = 0;
		pmlmeext->sitesurvey_res.channel_idx = 0;

		for (i = 0; i < RTW_SSID_SCAN_AMOUNT; i++) {
			if (pparm->ssid[i].SsidLength) {
				memcpy(pmlmeext->sitesurvey_res.ssid[i].Ssid, pparm->ssid[i].Ssid, IW_ESSID_MAX_SIZE);
				pmlmeext->sitesurvey_res.ssid[i].SsidLength = pparm->ssid[i].SsidLength;
			} else {
				pmlmeext->sitesurvey_res.ssid[i].SsidLength = 0;
			}
		}

		pmlmeext->sitesurvey_res.ch_num = rtw_scan_ch_decision(padapter
			, pmlmeext->sitesurvey_res.ch, RTW_CHANNEL_SCAN_AMOUNT
			, pparm->ch, pparm->ch_num
		);

		pmlmeext->sitesurvey_res.scan_mode = pparm->scan_mode;

		/* issue null data if associating to the AP */
		if (is_client_associated_to_ap(padapter)) {
			pmlmeext->sitesurvey_res.state = SCAN_TXNULL;

			issue_nulldata(padapter, NULL, 1, 3, 500);

			bdelayscan = true;
		}
		if (bdelayscan) {
			/* delay 50ms to protect nulldata(1). */
			set_survey_timer(pmlmeext, 50);
			return H2C_SUCCESS;
		}
	}

	if ((pmlmeext->sitesurvey_res.state == SCAN_START) || (pmlmeext->sitesurvey_res.state == SCAN_TXNULL)) {
		/* disable dynamic functions, such as high power, DIG */
		Save_DM_Func_Flag(padapter);
		Switch_DM_Func(padapter, DYNAMIC_FUNC_DISABLE, false);

		/* config the initial gain under scaning, need to write the BB registers */
		initialgain = 0x1e;

		rtw_hal_set_hwreg(padapter, HW_VAR_INITIAL_GAIN, (u8 *)(&initialgain));

		/* set MSR to no link state */
		Set_MSR(padapter, _HW_STATE_NOLINK_);

		val8 = 1; /* under site survey */
		rtw_hal_set_hwreg(padapter, HW_VAR_MLME_SITESURVEY, (u8 *)(&val8));

		pmlmeext->sitesurvey_res.state = SCAN_PROCESS;
	}

	site_survey(padapter);

	return H2C_SUCCESS;

}