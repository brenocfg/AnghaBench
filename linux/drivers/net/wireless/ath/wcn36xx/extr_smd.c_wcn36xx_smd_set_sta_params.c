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
struct wcn36xx_vif {int /*<<< orphan*/  bss_index; int /*<<< orphan*/  encrypt_type; int /*<<< orphan*/  self_sta_index; } ;
struct wcn36xx_sta {int /*<<< orphan*/  supported_rates; int /*<<< orphan*/  aid; } ;
struct wcn36xx_hal_config_sta_params {int type; int short_preamble_supported; int /*<<< orphan*/  supported_rates; int /*<<< orphan*/  aid; int /*<<< orphan*/  max_sp_len; int /*<<< orphan*/  wmm_enabled; int /*<<< orphan*/  mac; int /*<<< orphan*/  bssid; scalar_t__ p2p; int /*<<< orphan*/  bssid_index; scalar_t__ max_ampdu_duration; int /*<<< orphan*/  mimo_ps; scalar_t__ uapsd; scalar_t__ action; scalar_t__ rmf; scalar_t__ rifs_mode; int /*<<< orphan*/  encrypt_type; int /*<<< orphan*/  listen_interval; int /*<<< orphan*/  sta_index; } ;
struct wcn36xx {int dummy; } ;
struct ieee80211_vif {scalar_t__ type; int /*<<< orphan*/ * addr; } ;
struct ieee80211_sta {int /*<<< orphan*/  max_sp; int /*<<< orphan*/  wme; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  WCN36XX_HAL_HT_MIMO_PS_STATIC ; 
 int /*<<< orphan*/  WCN36XX_HAL_STA_INVALID_IDX ; 
 int /*<<< orphan*/  WCN36XX_LISTEN_INTERVAL (struct wcn36xx*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wcn36xx_set_default_rates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_smd_set_sta_default_ht_params (struct wcn36xx_hal_config_sta_params*) ; 
 int /*<<< orphan*/  wcn36xx_smd_set_sta_ht_params (struct ieee80211_sta*,struct wcn36xx_hal_config_sta_params*) ; 
 struct wcn36xx_sta* wcn36xx_sta_to_priv (struct ieee80211_sta*) ; 
 struct wcn36xx_vif* wcn36xx_vif_to_priv (struct ieee80211_vif*) ; 

__attribute__((used)) static void wcn36xx_smd_set_sta_params(struct wcn36xx *wcn,
		struct ieee80211_vif *vif,
		struct ieee80211_sta *sta,
		struct wcn36xx_hal_config_sta_params *sta_params)
{
	struct wcn36xx_vif *vif_priv = wcn36xx_vif_to_priv(vif);
	struct wcn36xx_sta *sta_priv = NULL;
	if (vif->type == NL80211_IFTYPE_ADHOC ||
	    vif->type == NL80211_IFTYPE_AP ||
	    vif->type == NL80211_IFTYPE_MESH_POINT) {
		sta_params->type = 1;
		sta_params->sta_index = WCN36XX_HAL_STA_INVALID_IDX;
	} else {
		sta_params->type = 0;
		sta_params->sta_index = vif_priv->self_sta_index;
	}

	sta_params->listen_interval = WCN36XX_LISTEN_INTERVAL(wcn);

	/*
	 * In STA mode ieee80211_sta contains bssid and ieee80211_vif
	 * contains our mac address. In  AP mode we are bssid so vif
	 * contains bssid and ieee80211_sta contains mac.
	 */
	if (NL80211_IFTYPE_STATION == vif->type)
		memcpy(&sta_params->mac, vif->addr, ETH_ALEN);
	else
		memcpy(&sta_params->bssid, vif->addr, ETH_ALEN);

	sta_params->encrypt_type = vif_priv->encrypt_type;
	sta_params->short_preamble_supported = true;

	sta_params->rifs_mode = 0;
	sta_params->rmf = 0;
	sta_params->action = 0;
	sta_params->uapsd = 0;
	sta_params->mimo_ps = WCN36XX_HAL_HT_MIMO_PS_STATIC;
	sta_params->max_ampdu_duration = 0;
	sta_params->bssid_index = vif_priv->bss_index;
	sta_params->p2p = 0;

	if (sta) {
		sta_priv = wcn36xx_sta_to_priv(sta);
		if (NL80211_IFTYPE_STATION == vif->type)
			memcpy(&sta_params->bssid, sta->addr, ETH_ALEN);
		else
			memcpy(&sta_params->mac, sta->addr, ETH_ALEN);
		sta_params->wmm_enabled = sta->wme;
		sta_params->max_sp_len = sta->max_sp;
		sta_params->aid = sta_priv->aid;
		wcn36xx_smd_set_sta_ht_params(sta, sta_params);
		memcpy(&sta_params->supported_rates, &sta_priv->supported_rates,
			sizeof(sta_priv->supported_rates));
	} else {
		wcn36xx_set_default_rates(&sta_params->supported_rates);
		wcn36xx_smd_set_sta_default_ht_params(sta_params);
	}
}