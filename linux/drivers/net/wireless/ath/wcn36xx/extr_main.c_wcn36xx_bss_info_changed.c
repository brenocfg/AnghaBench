#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  ssid; int /*<<< orphan*/  length; } ;
struct wcn36xx_vif {int is_joining; int sta_assoc; void* bss_index; int /*<<< orphan*/  dtim_period; TYPE_1__ ssid; int /*<<< orphan*/  encrypt_type; } ;
struct wcn36xx_sta {int /*<<< orphan*/  aid; } ;
struct wcn36xx {int /*<<< orphan*/  conf_mutex; } ;
struct sk_buff {int dummy; } ;
struct ieee80211_vif {scalar_t__ type; int /*<<< orphan*/  addr; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {struct wcn36xx* priv; } ;
struct ieee80211_bss_conf {int /*<<< orphan*/  dtim_period; int /*<<< orphan*/  enable_beacon; int /*<<< orphan*/  bssid; int /*<<< orphan*/  aid; scalar_t__ assoc; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
typedef  enum wcn36xx_hal_link_state { ____Placeholder_wcn36xx_hal_link_state } wcn36xx_hal_link_state ;

/* Variables and functions */
 int BSS_CHANGED_AP_PROBE_RESP ; 
 int BSS_CHANGED_ASSOC ; 
 int BSS_CHANGED_BEACON ; 
 int BSS_CHANGED_BEACON_ENABLED ; 
 int BSS_CHANGED_BEACON_INFO ; 
 int BSS_CHANGED_BSSID ; 
 int BSS_CHANGED_SSID ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  WCN36XX_BAND (struct wcn36xx*) ; 
 int /*<<< orphan*/  WCN36XX_DBG_MAC ; 
 void* WCN36XX_HAL_BSS_INVALID_IDX ; 
 int /*<<< orphan*/  WCN36XX_HAL_ED_NONE ; 
 int WCN36XX_HAL_LINK_AP_STATE ; 
 int WCN36XX_HAL_LINK_IBSS_STATE ; 
 int WCN36XX_HAL_LINK_IDLE_STATE ; 
 int WCN36XX_HAL_LINK_POSTASSOC_STATE ; 
 int WCN36XX_HAL_LINK_PREASSOC_STATE ; 
 int /*<<< orphan*/  WCN36XX_HW_CHANNEL (struct wcn36xx*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sk_buff* ieee80211_beacon_get_tim (struct ieee80211_hw*,struct ieee80211_vif*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ieee80211_sta* ieee80211_find_sta (struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 struct sk_buff* ieee80211_proberesp_get (struct ieee80211_hw*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wcn36xx_dbg_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,...) ; 
 int /*<<< orphan*/  wcn36xx_smd_config_bss (struct wcn36xx*,struct ieee80211_vif*,struct ieee80211_sta*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wcn36xx_smd_config_sta (struct wcn36xx*,struct ieee80211_vif*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  wcn36xx_smd_delete_bss (struct wcn36xx*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  wcn36xx_smd_join (struct wcn36xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_smd_send_beacon (struct wcn36xx*,struct ieee80211_vif*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_smd_set_link_st (struct wcn36xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wcn36xx_smd_update_proberesp_tmpl (struct wcn36xx*,struct ieee80211_vif*,struct sk_buff*) ; 
 struct wcn36xx_sta* wcn36xx_sta_to_priv (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  wcn36xx_update_allowed_rates (struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 struct wcn36xx_vif* wcn36xx_vif_to_priv (struct ieee80211_vif*) ; 

__attribute__((used)) static void wcn36xx_bss_info_changed(struct ieee80211_hw *hw,
				     struct ieee80211_vif *vif,
				     struct ieee80211_bss_conf *bss_conf,
				     u32 changed)
{
	struct wcn36xx *wcn = hw->priv;
	struct sk_buff *skb = NULL;
	u16 tim_off, tim_len;
	enum wcn36xx_hal_link_state link_state;
	struct wcn36xx_vif *vif_priv = wcn36xx_vif_to_priv(vif);

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac bss info changed vif %p changed 0x%08x\n",
		    vif, changed);

	mutex_lock(&wcn->conf_mutex);

	if (changed & BSS_CHANGED_BEACON_INFO) {
		wcn36xx_dbg(WCN36XX_DBG_MAC,
			    "mac bss changed dtim period %d\n",
			    bss_conf->dtim_period);

		vif_priv->dtim_period = bss_conf->dtim_period;
	}

	if (changed & BSS_CHANGED_BSSID) {
		wcn36xx_dbg(WCN36XX_DBG_MAC, "mac bss changed_bssid %pM\n",
			    bss_conf->bssid);

		if (!is_zero_ether_addr(bss_conf->bssid)) {
			vif_priv->is_joining = true;
			vif_priv->bss_index = WCN36XX_HAL_BSS_INVALID_IDX;
			wcn36xx_smd_set_link_st(wcn, bss_conf->bssid, vif->addr,
						WCN36XX_HAL_LINK_PREASSOC_STATE);
			wcn36xx_smd_join(wcn, bss_conf->bssid,
					 vif->addr, WCN36XX_HW_CHANNEL(wcn));
			wcn36xx_smd_config_bss(wcn, vif, NULL,
					       bss_conf->bssid, false);
		} else {
			vif_priv->is_joining = false;
			wcn36xx_smd_delete_bss(wcn, vif);
			wcn36xx_smd_set_link_st(wcn, bss_conf->bssid, vif->addr,
						WCN36XX_HAL_LINK_IDLE_STATE);
			vif_priv->encrypt_type = WCN36XX_HAL_ED_NONE;
		}
	}

	if (changed & BSS_CHANGED_SSID) {
		wcn36xx_dbg(WCN36XX_DBG_MAC,
			    "mac bss changed ssid\n");
		wcn36xx_dbg_dump(WCN36XX_DBG_MAC, "ssid ",
				 bss_conf->ssid, bss_conf->ssid_len);

		vif_priv->ssid.length = bss_conf->ssid_len;
		memcpy(&vif_priv->ssid.ssid,
		       bss_conf->ssid,
		       bss_conf->ssid_len);
	}

	if (changed & BSS_CHANGED_ASSOC) {
		vif_priv->is_joining = false;
		if (bss_conf->assoc) {
			struct ieee80211_sta *sta;
			struct wcn36xx_sta *sta_priv;

			wcn36xx_dbg(WCN36XX_DBG_MAC,
				    "mac assoc bss %pM vif %pM AID=%d\n",
				     bss_conf->bssid,
				     vif->addr,
				     bss_conf->aid);

			vif_priv->sta_assoc = true;

			/*
			 * Holding conf_mutex ensures mutal exclusion with
			 * wcn36xx_sta_remove() and as such ensures that sta
			 * won't be freed while we're operating on it. As such
			 * we do not need to hold the rcu_read_lock().
			 */
			sta = ieee80211_find_sta(vif, bss_conf->bssid);
			if (!sta) {
				wcn36xx_err("sta %pM is not found\n",
					      bss_conf->bssid);
				goto out;
			}
			sta_priv = wcn36xx_sta_to_priv(sta);

			wcn36xx_update_allowed_rates(sta, WCN36XX_BAND(wcn));

			wcn36xx_smd_set_link_st(wcn, bss_conf->bssid,
				vif->addr,
				WCN36XX_HAL_LINK_POSTASSOC_STATE);
			wcn36xx_smd_config_bss(wcn, vif, sta,
					       bss_conf->bssid,
					       true);
			sta_priv->aid = bss_conf->aid;
			/*
			 * config_sta must be called from  because this is the
			 * place where AID is available.
			 */
			wcn36xx_smd_config_sta(wcn, vif, sta);
		} else {
			wcn36xx_dbg(WCN36XX_DBG_MAC,
				    "disassociated bss %pM vif %pM AID=%d\n",
				    bss_conf->bssid,
				    vif->addr,
				    bss_conf->aid);
			vif_priv->sta_assoc = false;
			wcn36xx_smd_set_link_st(wcn,
						bss_conf->bssid,
						vif->addr,
						WCN36XX_HAL_LINK_IDLE_STATE);
		}
	}

	if (changed & BSS_CHANGED_AP_PROBE_RESP) {
		wcn36xx_dbg(WCN36XX_DBG_MAC, "mac bss changed ap probe resp\n");
		skb = ieee80211_proberesp_get(hw, vif);
		if (!skb) {
			wcn36xx_err("failed to alloc probereq skb\n");
			goto out;
		}

		wcn36xx_smd_update_proberesp_tmpl(wcn, vif, skb);
		dev_kfree_skb(skb);
	}

	if (changed & BSS_CHANGED_BEACON_ENABLED ||
	    changed & BSS_CHANGED_BEACON) {
		wcn36xx_dbg(WCN36XX_DBG_MAC,
			    "mac bss changed beacon enabled %d\n",
			    bss_conf->enable_beacon);

		if (bss_conf->enable_beacon) {
			vif_priv->dtim_period = bss_conf->dtim_period;
			vif_priv->bss_index = WCN36XX_HAL_BSS_INVALID_IDX;
			wcn36xx_smd_config_bss(wcn, vif, NULL,
					       vif->addr, false);
			skb = ieee80211_beacon_get_tim(hw, vif, &tim_off,
						       &tim_len);
			if (!skb) {
				wcn36xx_err("failed to alloc beacon skb\n");
				goto out;
			}
			wcn36xx_smd_send_beacon(wcn, vif, skb, tim_off, 0);
			dev_kfree_skb(skb);

			if (vif->type == NL80211_IFTYPE_ADHOC ||
			    vif->type == NL80211_IFTYPE_MESH_POINT)
				link_state = WCN36XX_HAL_LINK_IBSS_STATE;
			else
				link_state = WCN36XX_HAL_LINK_AP_STATE;

			wcn36xx_smd_set_link_st(wcn, vif->addr, vif->addr,
						link_state);
		} else {
			wcn36xx_smd_delete_bss(wcn, vif);
			wcn36xx_smd_set_link_st(wcn, vif->addr, vif->addr,
						WCN36XX_HAL_LINK_IDLE_STATE);
		}
	}
out:

	mutex_unlock(&wcn->conf_mutex);

	return;
}