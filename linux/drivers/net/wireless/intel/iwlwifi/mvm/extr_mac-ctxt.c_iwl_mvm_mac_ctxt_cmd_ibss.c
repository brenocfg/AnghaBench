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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm_vif {int id; } ;
struct iwl_mvm {int dummy; } ;
struct TYPE_4__ {void* beacon_template; void* bi; } ;
struct iwl_mac_ctx_cmd {TYPE_2__ ibss; void* filter_flags; } ;
struct TYPE_3__ {int beacon_int; } ;
struct ieee80211_vif {scalar_t__ type; TYPE_1__ bss_conf; } ;

/* Variables and functions */
 int MAC_FILTER_ACCEPT_GRP ; 
 int MAC_FILTER_IN_BEACON ; 
 int MAC_FILTER_IN_PROBE_REQUEST ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_cmd_common (struct iwl_mvm*,struct ieee80211_vif*,struct iwl_mac_ctx_cmd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iwl_mvm_mac_ctxt_send_cmd (struct iwl_mvm*,struct iwl_mac_ctx_cmd*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static int iwl_mvm_mac_ctxt_cmd_ibss(struct iwl_mvm *mvm,
				     struct ieee80211_vif *vif,
				     u32 action)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mac_ctx_cmd cmd = {};

	WARN_ON(vif->type != NL80211_IFTYPE_ADHOC);

	iwl_mvm_mac_ctxt_cmd_common(mvm, vif, &cmd, NULL, action);

	cmd.filter_flags = cpu_to_le32(MAC_FILTER_IN_BEACON |
				       MAC_FILTER_IN_PROBE_REQUEST |
				       MAC_FILTER_ACCEPT_GRP);

	/* cmd.ibss.beacon_time/cmd.ibss.beacon_tsf are curently ignored */
	cmd.ibss.bi = cpu_to_le32(vif->bss_conf.beacon_int);

	/* TODO: Assumes that the beacon id == mac context id */
	cmd.ibss.beacon_template = cpu_to_le32(mvmvif->id);

	return iwl_mvm_mac_ctxt_send_cmd(mvm, &cmd);
}