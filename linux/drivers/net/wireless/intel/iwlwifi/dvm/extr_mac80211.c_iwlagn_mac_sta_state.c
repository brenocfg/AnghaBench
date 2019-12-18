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
struct iwl_vif_priv {int /*<<< orphan*/  ctx; } ;
struct iwl_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  sta_lock; TYPE_1__* stations; } ;
struct ieee80211_vif {scalar_t__ type; scalar_t__ drv_priv; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum ieee80211_sta_state { ____Placeholder_ieee80211_sta_state } ieee80211_sta_state ;
struct TYPE_2__ {int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int IEEE80211_STA_ASSOC ; 
 int IEEE80211_STA_AUTH ; 
 int IEEE80211_STA_NONE ; 
 int IEEE80211_STA_NOTEXIST ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_priv*,char*,...) ; 
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  IWL_STA_UCODE_INPROGRESS ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ iwl_is_rfkill (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_rs_rate_init (struct iwl_priv*,struct ieee80211_sta*,size_t) ; 
 size_t iwl_sta_id (struct ieee80211_sta*) ; 
 int iwl_sta_update_ht (struct iwl_priv*,int /*<<< orphan*/ ,struct ieee80211_sta*) ; 
 int iwlagn_mac_sta_add (struct ieee80211_hw*,struct ieee80211_vif*,struct ieee80211_sta*) ; 
 int iwlagn_mac_sta_remove (struct ieee80211_hw*,struct ieee80211_vif*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwlagn_mac_sta_state(struct ieee80211_hw *hw,
				struct ieee80211_vif *vif,
				struct ieee80211_sta *sta,
				enum ieee80211_sta_state old_state,
				enum ieee80211_sta_state new_state)
{
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	struct iwl_vif_priv *vif_priv = (void *)vif->drv_priv;
	enum {
		NONE, ADD, REMOVE, HT_RATE_INIT, ADD_RATE_INIT,
	} op = NONE;
	int ret;

	IWL_DEBUG_MAC80211(priv, "station %pM state change %d->%d\n",
			   sta->addr, old_state, new_state);

	mutex_lock(&priv->mutex);
	if (vif->type == NL80211_IFTYPE_STATION) {
		if (old_state == IEEE80211_STA_NOTEXIST &&
		    new_state == IEEE80211_STA_NONE)
			op = ADD;
		else if (old_state == IEEE80211_STA_NONE &&
			 new_state == IEEE80211_STA_NOTEXIST)
			op = REMOVE;
		else if (old_state == IEEE80211_STA_AUTH &&
			 new_state == IEEE80211_STA_ASSOC)
			op = HT_RATE_INIT;
	} else {
		if (old_state == IEEE80211_STA_AUTH &&
		    new_state == IEEE80211_STA_ASSOC)
			op = ADD_RATE_INIT;
		else if (old_state == IEEE80211_STA_ASSOC &&
			 new_state == IEEE80211_STA_AUTH)
			op = REMOVE;
	}

	switch (op) {
	case ADD:
		ret = iwlagn_mac_sta_add(hw, vif, sta);
		if (ret)
			break;
		/*
		 * Clear the in-progress flag, the AP station entry was added
		 * but we'll initialize LQ only when we've associated (which
		 * would also clear the in-progress flag). This is necessary
		 * in case we never initialize LQ because association fails.
		 */
		spin_lock_bh(&priv->sta_lock);
		priv->stations[iwl_sta_id(sta)].used &=
			~IWL_STA_UCODE_INPROGRESS;
		spin_unlock_bh(&priv->sta_lock);
		break;
	case REMOVE:
		ret = iwlagn_mac_sta_remove(hw, vif, sta);
		break;
	case ADD_RATE_INIT:
		ret = iwlagn_mac_sta_add(hw, vif, sta);
		if (ret)
			break;
		/* Initialize rate scaling */
		IWL_DEBUG_INFO(priv,
			       "Initializing rate scaling for station %pM\n",
			       sta->addr);
		iwl_rs_rate_init(priv, sta, iwl_sta_id(sta));
		ret = 0;
		break;
	case HT_RATE_INIT:
		/* Initialize rate scaling */
		ret = iwl_sta_update_ht(priv, vif_priv->ctx, sta);
		if (ret)
			break;
		IWL_DEBUG_INFO(priv,
			       "Initializing rate scaling for station %pM\n",
			       sta->addr);
		iwl_rs_rate_init(priv, sta, iwl_sta_id(sta));
		ret = 0;
		break;
	default:
		ret = 0;
		break;
	}

	/*
	 * mac80211 might WARN if we fail, but due the way we
	 * (badly) handle hard rfkill, we might fail here
	 */
	if (iwl_is_rfkill(priv))
		ret = 0;

	mutex_unlock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "leave\n");

	return ret;
}