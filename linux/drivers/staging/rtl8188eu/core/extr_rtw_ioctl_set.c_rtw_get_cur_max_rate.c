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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct wlan_bssid_ex {int* SupportedRates; scalar_t__ ie_length; int /*<<< orphan*/ * ies; } ;
struct registry_priv {int cbw40_enable; } ;
struct TYPE_5__ {struct wlan_bssid_ex network; } ;
struct mlme_priv {TYPE_1__ cur_network; } ;
struct TYPE_7__ {int /*<<< orphan*/  rx_mask; } ;
struct TYPE_8__ {TYPE_3__ mcs; int /*<<< orphan*/  cap_info; } ;
struct TYPE_6__ {int* infos; } ;
struct mlme_ext_info {TYPE_4__ HT_caps; TYPE_2__ HT_info; } ;
struct mlme_ext_priv {int cur_wireless_mode; scalar_t__ cur_bwmode; struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_priv mlmepriv; struct registry_priv registrypriv; struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int HT_INFO_HT_PARAM_REC_TRANS_CHNL_WIDTH ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int /*<<< orphan*/  RF_1T1R ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int WIRELESS_11_24N ; 
 int WIRELESS_11_5N ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  _HT_CAPABILITY_IE_ ; 
 int /*<<< orphan*/  check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int* rtw_get_ie (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int rtw_mcs_rate (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 

u16 rtw_get_cur_max_rate(struct adapter *adapter)
{
	int i = 0;
	u8 *p;
	u16 rate = 0, max_rate = 0;
	struct mlme_ext_priv *pmlmeext = &adapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	struct registry_priv *pregistrypriv = &adapter->registrypriv;
	struct mlme_priv *pmlmepriv = &adapter->mlmepriv;
	struct wlan_bssid_ex *pcur_bss = &pmlmepriv->cur_network.network;
	u8 bw_40MHz = 0, short_GI_20 = 0, short_GI_40 = 0;
	u32 ht_ielen = 0;

	if (!check_fwstate(pmlmepriv, _FW_LINKED) &&
	    !check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE))
		return 0;

	if (pmlmeext->cur_wireless_mode & (WIRELESS_11_24N | WIRELESS_11_5N)) {
		p = rtw_get_ie(&pcur_bss->ies[12], _HT_CAPABILITY_IE_,
			       &ht_ielen, pcur_bss->ie_length - 12);
		if (p && ht_ielen > 0) {
			/* cur_bwmod is updated by beacon, pmlmeinfo is updated by association response */
			bw_40MHz = (pmlmeext->cur_bwmode && (HT_INFO_HT_PARAM_REC_TRANS_CHNL_WIDTH & pmlmeinfo->HT_info.infos[0])) ? 1 : 0;

			short_GI_20 = (le16_to_cpu(pmlmeinfo->HT_caps.cap_info) & IEEE80211_HT_CAP_SGI_20) ? 1 : 0;
			short_GI_40 = (le16_to_cpu(pmlmeinfo->HT_caps.cap_info) & IEEE80211_HT_CAP_SGI_40) ? 1 : 0;

			max_rate = rtw_mcs_rate(
				RF_1T1R,
				bw_40MHz & pregistrypriv->cbw40_enable,
				short_GI_20,
				short_GI_40,
				pmlmeinfo->HT_caps.mcs.rx_mask
			);
		}
	} else {
		while (pcur_bss->SupportedRates[i] != 0 &&
		       pcur_bss->SupportedRates[i] != 0xFF) {
			rate = pcur_bss->SupportedRates[i] & 0x7F;
			if (rate > max_rate)
				max_rate = rate;
			i++;
		}

		max_rate *= 5;
	}

	return max_rate;
}