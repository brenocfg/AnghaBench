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
struct iwl_station_priv {int asleep; int /*<<< orphan*/  client; int /*<<< orphan*/  pending_frames; } ;
struct iwl_priv {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum sta_notify_cmd { ____Placeholder_sta_notify_cmd } sta_notify_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_priv*,char*) ; 
 int IWL_INVALID_STATION ; 
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
#define  STA_NOTIFY_AWAKE 129 
#define  STA_NOTIFY_SLEEP 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_sta_block_awake (struct ieee80211_hw*,struct ieee80211_sta*,int) ; 
 int iwl_sta_id (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  iwl_sta_modify_ps_wake (struct iwl_priv*,int) ; 

__attribute__((used)) static void iwlagn_mac_sta_notify(struct ieee80211_hw *hw,
				  struct ieee80211_vif *vif,
				  enum sta_notify_cmd cmd,
				  struct ieee80211_sta *sta)
{
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	struct iwl_station_priv *sta_priv = (void *)sta->drv_priv;
	int sta_id;

	IWL_DEBUG_MAC80211(priv, "enter\n");

	switch (cmd) {
	case STA_NOTIFY_SLEEP:
		WARN_ON(!sta_priv->client);
		sta_priv->asleep = true;
		if (atomic_read(&sta_priv->pending_frames) > 0)
			ieee80211_sta_block_awake(hw, sta, true);
		break;
	case STA_NOTIFY_AWAKE:
		WARN_ON(!sta_priv->client);
		if (!sta_priv->asleep)
			break;
		sta_priv->asleep = false;
		sta_id = iwl_sta_id(sta);
		if (sta_id != IWL_INVALID_STATION)
			iwl_sta_modify_ps_wake(priv, sta_id);
		break;
	default:
		break;
	}
	IWL_DEBUG_MAC80211(priv, "leave\n");
}