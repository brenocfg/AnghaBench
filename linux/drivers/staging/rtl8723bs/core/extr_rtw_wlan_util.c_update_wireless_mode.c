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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct wlan_bssid_ex {unsigned char* SupportedRates; } ;
struct mlme_ext_info {int HT_enable; scalar_t__ VHT_enable; scalar_t__ HT_caps_enable; scalar_t__ HT_info_enable; struct wlan_bssid_ex network; } ;
struct mlme_ext_priv {int cur_channel; int cur_wireless_mode; struct mlme_ext_info mlmext_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* SetHwRegHandler ) (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int wireless_mode; } ;
struct adapter {TYPE_2__ HalFunc; TYPE_1__ registrypriv; struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_RESP_SIFS ; 
 int /*<<< orphan*/  HW_VAR_WIRELESS_MODE ; 
 int /*<<< orphan*/  IEEE80211_CCK_RATE_1MB ; 
 int /*<<< orphan*/  IEEE80211_OFDM_RATE_6MB ; 
 int WIRELESS_11A ; 
 int WIRELESS_11AC ; 
 int WIRELESS_11B ; 
 int WIRELESS_11BG ; 
 int WIRELESS_11G ; 
 int WIRELESS_11_24N ; 
 int WIRELESS_11_5N ; 
 int cckrates_included (unsigned char*,int) ; 
 int cckratesonly_included (unsigned char*,int) ; 
 int rtw_get_rateset_len (unsigned char*) ; 
 int /*<<< orphan*/  stub1 (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_mgnt_tx_rate (struct adapter*,int /*<<< orphan*/ ) ; 

void update_wireless_mode(struct adapter *padapter)
{
	int ratelen, network_type = 0;
	u32 SIFS_Timer;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	struct wlan_bssid_ex		*cur_network = &(pmlmeinfo->network);
	unsigned char 		*rate = cur_network->SupportedRates;

	ratelen = rtw_get_rateset_len(cur_network->SupportedRates);

	if ((pmlmeinfo->HT_info_enable) && (pmlmeinfo->HT_caps_enable))
		pmlmeinfo->HT_enable = 1;

	if (pmlmeext->cur_channel > 14) {
		if (pmlmeinfo->VHT_enable)
			network_type = WIRELESS_11AC;
		else if (pmlmeinfo->HT_enable)
			network_type = WIRELESS_11_5N;

		network_type |= WIRELESS_11A;
	} else {
		if (pmlmeinfo->VHT_enable)
			network_type = WIRELESS_11AC;
		else if (pmlmeinfo->HT_enable)
			network_type = WIRELESS_11_24N;

		if ((cckratesonly_included(rate, ratelen)) == true)
			network_type |= WIRELESS_11B;
		else if ((cckrates_included(rate, ratelen)) == true)
			network_type |= WIRELESS_11BG;
		else
			network_type |= WIRELESS_11G;
	}

	pmlmeext->cur_wireless_mode = network_type & padapter->registrypriv.wireless_mode;

	SIFS_Timer = 0x0a0a0808; /* 0x0808 -> for CCK, 0x0a0a -> for OFDM */
													/* change this value if having IOT issues. */

	padapter->HalFunc.SetHwRegHandler(padapter, HW_VAR_RESP_SIFS,  (u8 *)&SIFS_Timer);

	padapter->HalFunc.SetHwRegHandler(padapter, HW_VAR_WIRELESS_MODE,  (u8 *)&(pmlmeext->cur_wireless_mode));

	if (pmlmeext->cur_wireless_mode & WIRELESS_11B)
		update_mgnt_tx_rate(padapter, IEEE80211_CCK_RATE_1MB);
	 else
		update_mgnt_tx_rate(padapter, IEEE80211_OFDM_RATE_6MB);
}