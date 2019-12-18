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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct iwl_mvm_vif {scalar_t__ id; } ;
struct iwl_mvm {int dummy; } ;
struct iwl_mac_beacon_cmd_v6 {int /*<<< orphan*/  tim_size; int /*<<< orphan*/  tim_idx; int /*<<< orphan*/  template_id; int /*<<< orphan*/  tx; } ;
struct ieee80211_vif {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  beacon_cmd ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int iwl_mvm_mac_ctxt_send_beacon_cmd (struct iwl_mvm*,struct sk_buff*,struct iwl_mac_beacon_cmd_v6*,int) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_set_tim (struct iwl_mvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_set_tx (struct iwl_mvm*,struct ieee80211_vif*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static int iwl_mvm_mac_ctxt_send_beacon_v6(struct iwl_mvm *mvm,
					   struct ieee80211_vif *vif,
					   struct sk_buff *beacon)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mac_beacon_cmd_v6 beacon_cmd = {};

	iwl_mvm_mac_ctxt_set_tx(mvm, vif, beacon, &beacon_cmd.tx);

	beacon_cmd.template_id = cpu_to_le32((u32)mvmvif->id);

	if (vif->type == NL80211_IFTYPE_AP)
		iwl_mvm_mac_ctxt_set_tim(mvm, &beacon_cmd.tim_idx,
					 &beacon_cmd.tim_size,
					 beacon->data, beacon->len);

	return iwl_mvm_mac_ctxt_send_beacon_cmd(mvm, beacon, &beacon_cmd,
						sizeof(beacon_cmd));
}