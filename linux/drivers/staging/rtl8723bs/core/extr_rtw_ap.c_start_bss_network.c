#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_5__ {int DSConfig; scalar_t__ BeaconPeriod; } ;
struct wlan_bssid_ex {int* MacAddress; int* SupportedRates; int /*<<< orphan*/  Length; scalar_t__ IELength; scalar_t__ IEs; TYPE_1__ Configuration; } ;
struct security_priv {scalar_t__ dot11PrivacyAlgrthm; scalar_t__ dot11AuthAlgrthm; } ;
struct registry_priv {int bw_mode; } ;
struct ndis_802_11_fix_ie {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  network_type; int /*<<< orphan*/  join_res; int /*<<< orphan*/  network; } ;
struct TYPE_7__ {scalar_t__ ht_option; } ;
struct TYPE_6__ {scalar_t__ qos_option; } ;
struct mlme_priv {TYPE_4__ cur_network; TYPE_3__ htpriv; TYPE_2__ qospriv; } ;
struct mlme_ext_info {int WMM_enable; int HT_enable; struct wlan_bssid_ex network; } ;
struct mlme_ext_priv {int bstart_bss; int cur_channel; int cur_bwmode; int cur_ch_offset; int /*<<< orphan*/  cur_wireless_mode; struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; struct security_priv securitypriv; struct mlme_priv mlmepriv; struct registry_priv registrypriv; } ;
struct HT_info_element {int* infos; } ;

/* Variables and functions */
 int BIT (int) ; 
 int CHANNEL_WIDTH_20 ; 
 int CHANNEL_WIDTH_40 ; 
 int /*<<< orphan*/  DBG_871X (char*,...) ; 
 int /*<<< orphan*/  DYNAMIC_ALL_FUNC_ENABLE ; 
 int HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 int HAL_PRIME_CHNL_OFFSET_LOWER ; 
 int HAL_PRIME_CHNL_OFFSET_UPPER ; 
 int /*<<< orphan*/  HW_VAR_AC_PARAM_BE ; 
 int /*<<< orphan*/  HW_VAR_AC_PARAM_BK ; 
 int /*<<< orphan*/  HW_VAR_AC_PARAM_VI ; 
 int /*<<< orphan*/  HW_VAR_AC_PARAM_VO ; 
 int /*<<< orphan*/  HW_VAR_BASIC_RATE ; 
 int /*<<< orphan*/  HW_VAR_BEACON_INTERVAL ; 
 int /*<<< orphan*/  HW_VAR_BSSID ; 
 int /*<<< orphan*/  HW_VAR_DO_IQK ; 
 int /*<<< orphan*/  HW_VAR_SEC_CFG ; 
 int /*<<< orphan*/  Set_MSR (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Switch_DM_Func (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UpdateBrateTbl (struct adapter*,int*) ; 
 scalar_t__ _FAIL ; 
 scalar_t__ _FIXED_IE_LENGTH_ ; 
 int /*<<< orphan*/  _HT_ADD_INFO_IE_ ; 
 int /*<<< orphan*/  _HW_STATE_AP_ ; 
 int /*<<< orphan*/  _TIM_IE_ ; 
 scalar_t__ _WEP104_ ; 
 scalar_t__ _WEP40_ ; 
 scalar_t__ dot11AuthAlgrthm_8021X ; 
 int /*<<< orphan*/  flush_all_cam_entry (struct adapter*) ; 
 int /*<<< orphan*/  memcpy (struct wlan_bssid_ex*,struct wlan_bssid_ex*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_get_capability (struct wlan_bssid_ex*) ; 
 int* rtw_get_ie (scalar_t__,int /*<<< orphan*/ ,int*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_get_wps_ie (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (struct adapter*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ send_beacon (struct adapter*) ; 
 int /*<<< orphan*/  set_channel_bwmode (struct adapter*,int,int,int) ; 
 int /*<<< orphan*/  update_beacon (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  update_bmc_sta (struct adapter*) ; 
 int /*<<< orphan*/  update_capinfo (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_hw_ht_param (struct adapter*) ; 
 int /*<<< orphan*/  update_wireless_mode (struct adapter*) ; 

void start_bss_network(struct adapter *padapter, u8 *pbuf)
{
	u8 *p;
	u8 val8, cur_channel, cur_bwmode, cur_ch_offset;
	u16 bcn_interval;
	u32 acparm;
	int	ie_len;
	struct registry_priv  *pregpriv = &padapter->registrypriv;
	struct mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	struct security_priv *psecuritypriv = &(padapter->securitypriv);
	struct wlan_bssid_ex
		*pnetwork = (struct wlan_bssid_ex *)&pmlmepriv->cur_network.network;
	struct mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	struct mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	struct wlan_bssid_ex *pnetwork_mlmeext = &(pmlmeinfo->network);
	struct HT_info_element *pht_info = NULL;
	u8 cbw40_enable = 0;

	/* DBG_871X("%s\n", __func__); */

	bcn_interval = (u16)pnetwork->Configuration.BeaconPeriod;
	cur_channel = pnetwork->Configuration.DSConfig;
	cur_bwmode = CHANNEL_WIDTH_20;
	cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

	/* check if there is wps ie, */
	/* if there is wpsie in beacon, the hostapd will update beacon twice when stating hostapd, */
	/* and at first time the security ie (RSN/WPA IE) will not include in beacon. */
	if (!rtw_get_wps_ie(pnetwork->IEs + _FIXED_IE_LENGTH_,
			    pnetwork->IELength - _FIXED_IE_LENGTH_, NULL, NULL))
		pmlmeext->bstart_bss = true;

	/* todo: update wmm, ht cap */
	/* pmlmeinfo->WMM_enable; */
	/* pmlmeinfo->HT_enable; */
	if (pmlmepriv->qospriv.qos_option)
		pmlmeinfo->WMM_enable = true;
	if (pmlmepriv->htpriv.ht_option) {
		pmlmeinfo->WMM_enable = true;
		pmlmeinfo->HT_enable = true;
		/* pmlmeinfo->HT_info_enable = true; */
		/* pmlmeinfo->HT_caps_enable = true; */

		update_hw_ht_param(padapter);
	}

	if (!pmlmepriv->cur_network.join_res) { /* setting only at  first time */

		/* WEP Key will be set before this function, do not clear CAM. */
		if (
			(psecuritypriv->dot11PrivacyAlgrthm != _WEP40_) &&
			(psecuritypriv->dot11PrivacyAlgrthm != _WEP104_)
		)
			flush_all_cam_entry(padapter);	/* clear CAM */
	}

	/* set MSR to AP_Mode */
	Set_MSR(padapter, _HW_STATE_AP_);

	/* Set BSSID REG */
	rtw_hal_set_hwreg(padapter, HW_VAR_BSSID, pnetwork->MacAddress);

	/* Set EDCA param reg */
	acparm = 0x002F3217; /*  VO */
	rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_VO, (u8 *)(&acparm));
	acparm = 0x005E4317; /*  VI */
	rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_VI, (u8 *)(&acparm));
	/* acparm = 0x00105320; // BE */
	acparm = 0x005ea42b;
	rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_BE, (u8 *)(&acparm));
	acparm = 0x0000A444; /*  BK */
	rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_BK, (u8 *)(&acparm));

	/* Set Security */
	val8 = (
		psecuritypriv->dot11AuthAlgrthm == dot11AuthAlgrthm_8021X
	) ? 0xcc : 0xcf;
	rtw_hal_set_hwreg(padapter, HW_VAR_SEC_CFG, (u8 *)(&val8));

	/* Beacon Control related register */
	rtw_hal_set_hwreg(padapter, HW_VAR_BEACON_INTERVAL, (u8 *)(&bcn_interval));

	rtw_hal_set_hwreg(padapter, HW_VAR_DO_IQK, NULL);

	if (!pmlmepriv->cur_network.join_res) { /* setting only at  first time */
		/* u32 initialgain; */

		/* initialgain = 0x1e; */

		/* disable dynamic functions, such as high power, DIG */
		/* Save_DM_Func_Flag(padapter); */
		/* Switch_DM_Func(padapter, DYNAMIC_FUNC_DISABLE, false); */

		/* turn on all dynamic functions */
		Switch_DM_Func(padapter, DYNAMIC_ALL_FUNC_ENABLE, true);

		/* rtw_hal_set_hwreg(padapter, HW_VAR_INITIAL_GAIN, (u8 *)(&initialgain)); */
	}

	/* set channel, bwmode */
	p = rtw_get_ie(
		(pnetwork->IEs + sizeof(struct ndis_802_11_fix_ie)),
		_HT_ADD_INFO_IE_,
		&ie_len,
		(pnetwork->IELength - sizeof(struct ndis_802_11_fix_ie))
	);
	if (p && ie_len) {
		pht_info = (struct HT_info_element *)(p + 2);

		if (cur_channel > 14) {
			if ((pregpriv->bw_mode & 0xf0) > 0)
				cbw40_enable = 1;
		} else {
			if ((pregpriv->bw_mode & 0x0f) > 0)
				cbw40_enable = 1;
		}

		if ((cbw40_enable) &&	 (pht_info->infos[0] & BIT(2))) {
			/* switch to the 40M Hz mode */
			/* pmlmeext->cur_bwmode = CHANNEL_WIDTH_40; */
			cur_bwmode = CHANNEL_WIDTH_40;
			switch (pht_info->infos[0] & 0x3) {
			case 1:
				/* pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_LOWER; */
				cur_ch_offset = HAL_PRIME_CHNL_OFFSET_LOWER;
				break;

			case 3:
				/* pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_UPPER; */
				cur_ch_offset = HAL_PRIME_CHNL_OFFSET_UPPER;
				break;

			default:
				/* pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE; */
				cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
				break;
			}
		}
	}

	set_channel_bwmode(padapter, cur_channel, cur_ch_offset, cur_bwmode);
	DBG_871X(
		"CH =%d, BW =%d, offset =%d\n",
		cur_channel,
		cur_bwmode,
		cur_ch_offset
	);
	pmlmeext->cur_channel = cur_channel;
	pmlmeext->cur_bwmode = cur_bwmode;
	pmlmeext->cur_ch_offset = cur_ch_offset;
	pmlmeext->cur_wireless_mode = pmlmepriv->cur_network.network_type;

	/* let pnetwork_mlmeext == pnetwork_mlme. */
	memcpy(pnetwork_mlmeext, pnetwork, pnetwork->Length);

	/* update cur_wireless_mode */
	update_wireless_mode(padapter);

	/* update RRSR after set channel and bandwidth */
	UpdateBrateTbl(padapter, pnetwork->SupportedRates);
	rtw_hal_set_hwreg(padapter, HW_VAR_BASIC_RATE, pnetwork->SupportedRates);

	/* update capability after cur_wireless_mode updated */
	update_capinfo(
		padapter,
		rtw_get_capability((struct wlan_bssid_ex *)pnetwork)
	);

	if (pmlmeext->bstart_bss) {
		update_beacon(padapter, _TIM_IE_, NULL, true);

#ifndef CONFIG_INTERRUPT_BASED_TXBCN /* other case will  tx beacon when bcn interrupt coming in. */
		/* issue beacon frame */
		if (send_beacon(padapter) == _FAIL)
			DBG_871X("issue_beacon, fail!\n");

#endif /* CONFIG_INTERRUPT_BASED_TXBCN */
	}

	/* update bc/mc sta_info */
	update_bmc_sta(padapter);

	/* pmlmeext->bstart_bss = true; */
}