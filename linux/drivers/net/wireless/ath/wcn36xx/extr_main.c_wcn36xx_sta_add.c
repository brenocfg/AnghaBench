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
struct wcn36xx_vif {int /*<<< orphan*/  sta_list; } ;
struct wcn36xx_sta {int /*<<< orphan*/  aid; int /*<<< orphan*/  list; struct wcn36xx_vif* vif; int /*<<< orphan*/  ampdu_lock; } ;
struct wcn36xx {int /*<<< orphan*/  conf_mutex; } ;
struct ieee80211_vif {scalar_t__ type; } ;
struct ieee80211_sta {int /*<<< orphan*/  aid; int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {struct wcn36xx* priv; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  WCN36XX_BAND (struct wcn36xx*) ; 
 int /*<<< orphan*/  WCN36XX_DBG_MAC ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_smd_config_sta (struct wcn36xx*,struct ieee80211_vif*,struct ieee80211_sta*) ; 
 struct wcn36xx_sta* wcn36xx_sta_to_priv (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  wcn36xx_update_allowed_rates (struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 struct wcn36xx_vif* wcn36xx_vif_to_priv (struct ieee80211_vif*) ; 

__attribute__((used)) static int wcn36xx_sta_add(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			   struct ieee80211_sta *sta)
{
	struct wcn36xx *wcn = hw->priv;
	struct wcn36xx_vif *vif_priv = wcn36xx_vif_to_priv(vif);
	struct wcn36xx_sta *sta_priv = wcn36xx_sta_to_priv(sta);
	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac sta add vif %p sta %pM\n",
		    vif, sta->addr);

	mutex_lock(&wcn->conf_mutex);

	spin_lock_init(&sta_priv->ampdu_lock);
	sta_priv->vif = vif_priv;
	list_add(&sta_priv->list, &vif_priv->sta_list);

	/*
	 * For STA mode HW will be configured on BSS_CHANGED_ASSOC because
	 * at this stage AID is not available yet.
	 */
	if (NL80211_IFTYPE_STATION != vif->type) {
		wcn36xx_update_allowed_rates(sta, WCN36XX_BAND(wcn));
		sta_priv->aid = sta->aid;
		wcn36xx_smd_config_sta(wcn, vif, sta);
	}

	mutex_unlock(&wcn->conf_mutex);

	return 0;
}