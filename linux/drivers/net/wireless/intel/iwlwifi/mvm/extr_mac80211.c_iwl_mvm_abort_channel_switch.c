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
struct iwl_mvm_vif {int /*<<< orphan*/  id; int /*<<< orphan*/  color; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct iwl_chan_switch_te_cmd {int /*<<< orphan*/  action; int /*<<< orphan*/  mac_id; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_SWITCH_TIME_EVENT_CMD ; 
 int /*<<< orphan*/  FW_CMD_ID_AND_COLOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_CTXT_ACTION_REMOVE ; 
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_mvm*,char*,int /*<<< orphan*/ ) ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  MAC_CONF_GROUP ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIDE_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_post_channel_switch (struct ieee80211_hw*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_chan_switch_te_cmd*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_abort_channel_switch(struct ieee80211_hw *hw,
					 struct ieee80211_vif *vif)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_chan_switch_te_cmd cmd = {
		.mac_id = cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvif->id,
							  mvmvif->color)),
		.action = cpu_to_le32(FW_CTXT_ACTION_REMOVE),
	};

	IWL_DEBUG_MAC80211(mvm, "Abort CSA on mac %d\n", mvmvif->id);

	mutex_lock(&mvm->mutex);
	WARN_ON(iwl_mvm_send_cmd_pdu(mvm,
				     WIDE_ID(MAC_CONF_GROUP,
					     CHANNEL_SWITCH_TIME_EVENT_CMD),
				     0, sizeof(cmd), &cmd));
	mutex_unlock(&mvm->mutex);

	WARN_ON(iwl_mvm_post_channel_switch(hw, vif));
}