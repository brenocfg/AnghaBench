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
struct wlan_bssid_ex {int /*<<< orphan*/  MacAddress; } ;
struct sta_priv {int dummy; } ;
struct ht_priv {unsigned char bwmode; unsigned char ch_offset; scalar_t__ ht_option; } ;
struct sta_info {struct ht_priv htpriv; } ;
struct registry_priv {scalar_t__ cbw40_enable; } ;
struct ndis_802_11_var_ie {int Length; scalar_t__ data; } ;
struct mlme_priv {struct ht_priv htpriv; } ;
struct mlme_ext_info {int bwmode_updated; struct wlan_bssid_ex network; } ;
struct mlme_ext_priv {unsigned char cur_bwmode; unsigned char cur_ch_offset; struct mlme_ext_info mlmext_info; } ;
struct adapter {struct sta_priv stapriv; struct registry_priv registrypriv; struct mlme_ext_priv mlmeextpriv; struct mlme_priv mlmepriv; } ;
struct HT_info_element {int* infos; } ;

/* Variables and functions */
 int BIT (int) ; 
 void* HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 unsigned char HAL_PRIME_CHNL_OFFSET_LOWER ; 
 unsigned char HAL_PRIME_CHNL_OFFSET_UPPER ; 
 void* HT_CHANNEL_WIDTH_20 ; 
 unsigned char HT_CHANNEL_WIDTH_40 ; 
 int /*<<< orphan*/  HT_info_handler (struct adapter*,struct ndis_802_11_var_ie*) ; 
 struct sta_info* rtw_get_stainfo (struct sta_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bwmode_update_check(struct adapter *padapter, struct ndis_802_11_var_ie *pIE)
{
	unsigned char new_bwmode;
	unsigned char new_ch_offset;
	struct HT_info_element *pHT_info;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	struct registry_priv *pregistrypriv = &padapter->registrypriv;
	struct ht_priv *phtpriv = &pmlmepriv->htpriv;

	if (!pIE)
		return;

	if (!phtpriv)
		return;

	if (pIE->Length > sizeof(struct HT_info_element))
		return;

	pHT_info = (struct HT_info_element *)pIE->data;

	if ((pHT_info->infos[0] & BIT(2)) && pregistrypriv->cbw40_enable) {
		new_bwmode = HT_CHANNEL_WIDTH_40;

		switch (pHT_info->infos[0] & 0x3) {
		case 1:
			new_ch_offset = HAL_PRIME_CHNL_OFFSET_LOWER;
			break;
		case 3:
			new_ch_offset = HAL_PRIME_CHNL_OFFSET_UPPER;
			break;
		default:
			new_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
			break;
		}
	} else {
		new_bwmode = HT_CHANNEL_WIDTH_20;
		new_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
	}

	if ((new_bwmode != pmlmeext->cur_bwmode) ||
	    (new_ch_offset != pmlmeext->cur_ch_offset)) {
		pmlmeinfo->bwmode_updated = true;

		pmlmeext->cur_bwmode = new_bwmode;
		pmlmeext->cur_ch_offset = new_ch_offset;

		/* update HT info also */
		HT_info_handler(padapter, pIE);
	} else {
		pmlmeinfo->bwmode_updated = false;
	}

	if (pmlmeinfo->bwmode_updated) {
		struct sta_info *psta;
		struct wlan_bssid_ex	*cur_network = &pmlmeinfo->network;
		struct sta_priv	*pstapriv = &padapter->stapriv;

		/* update ap's stainfo */
		psta = rtw_get_stainfo(pstapriv, cur_network->MacAddress);
		if (psta) {
			struct ht_priv	*phtpriv_sta = &psta->htpriv;

			if (phtpriv_sta->ht_option) {
				/*  bwmode */
				phtpriv_sta->bwmode = pmlmeext->cur_bwmode;
				phtpriv_sta->ch_offset = pmlmeext->cur_ch_offset;
			} else {
				phtpriv_sta->bwmode = HT_CHANNEL_WIDTH_20;
				phtpriv_sta->ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
			}
		}
	}
}