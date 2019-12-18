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
struct wlan_bssid_ex {struct ht_priv* SupportedRates; } ;
struct sta_info {int bssratelen; int qos_option; int /*<<< orphan*/  htpriv; int /*<<< orphan*/  bw_mode; int /*<<< orphan*/ * bssrateset; int /*<<< orphan*/  wireless_mode; } ;
struct TYPE_4__ {int cap_info; } ;
struct ht_priv {int sgi_20m; int sgi_40m; int ampdu_enable; int agg_enable_bitmap; int candidate_tid_bitmap; int /*<<< orphan*/  ch_offset; TYPE_2__ ht_cap; scalar_t__ ht_option; } ;
struct TYPE_3__ {int /*<<< orphan*/  network; } ;
struct mlme_priv {struct ht_priv htpriv; TYPE_1__ cur_network; } ;
struct mlme_ext_priv {int /*<<< orphan*/  cur_ch_offset; int /*<<< orphan*/  cur_bwmode; int /*<<< orphan*/  cur_wireless_mode; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_HT_CAP_SGI_20 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SGI_40 ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ht_priv*,int) ; 
 int rtw_get_rateset_len (struct ht_priv*) ; 

__attribute__((used)) static void update_ap_info(struct adapter *padapter, struct sta_info *psta)
{
	struct mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	struct wlan_bssid_ex
		*pnetwork = (struct wlan_bssid_ex *)&pmlmepriv->cur_network.network;
	struct mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	struct ht_priv *phtpriv_ap = &pmlmepriv->htpriv;

	psta->wireless_mode = pmlmeext->cur_wireless_mode;

	psta->bssratelen = rtw_get_rateset_len(pnetwork->SupportedRates);
	memcpy(psta->bssrateset, pnetwork->SupportedRates, psta->bssratelen);

	/* HT related cap */
	if (phtpriv_ap->ht_option) {
		/* check if sta supports rx ampdu */
		/* phtpriv_ap->ampdu_enable = phtpriv_ap->ampdu_enable; */

		/* check if sta support s Short GI 20M */
		if ((phtpriv_ap->ht_cap.cap_info) & cpu_to_le16(IEEE80211_HT_CAP_SGI_20))
			phtpriv_ap->sgi_20m = true;

		/* check if sta support s Short GI 40M */
		if ((phtpriv_ap->ht_cap.cap_info) & cpu_to_le16(IEEE80211_HT_CAP_SGI_40))
			phtpriv_ap->sgi_40m = true;

		psta->qos_option = true;
	} else {
		phtpriv_ap->ampdu_enable = false;

		phtpriv_ap->sgi_20m = false;
		phtpriv_ap->sgi_40m = false;
	}

	psta->bw_mode = pmlmeext->cur_bwmode;
	phtpriv_ap->ch_offset = pmlmeext->cur_ch_offset;

	phtpriv_ap->agg_enable_bitmap = 0x0;/* reset */
	phtpriv_ap->candidate_tid_bitmap = 0x0;/* reset */

	memcpy(&psta->htpriv, &pmlmepriv->htpriv, sizeof(struct ht_priv));
}