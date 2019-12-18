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
struct iwl_mvm {int /*<<< orphan*/  snif_sta; int /*<<< orphan*/  hw; int /*<<< orphan*/  snif_queue; } ;
struct iwl_mac_ctx_cmd {int /*<<< orphan*/  filter_flags; } ;
struct ieee80211_vif {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_STA_GENERAL_PURPOSE ; 
 int MAC_FILTER_ACCEPT_GRP ; 
 int MAC_FILTER_IN_BEACON ; 
 int MAC_FILTER_IN_CONTROL_AND_MGMT ; 
 int MAC_FILTER_IN_CRC32 ; 
 int MAC_FILTER_IN_PROBE_REQUEST ; 
 int MAC_FILTER_IN_PROMISC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MONITOR ; 
 int /*<<< orphan*/  RX_INCLUDES_FCS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ieee80211_hw_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_mvm_allocate_int_sta (struct iwl_mvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_cmd_common (struct iwl_mvm*,struct ieee80211_vif*,struct iwl_mac_ctx_cmd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iwl_mvm_mac_ctxt_send_cmd (struct iwl_mvm*,struct iwl_mac_ctx_cmd*) ; 

__attribute__((used)) static int iwl_mvm_mac_ctxt_cmd_listener(struct iwl_mvm *mvm,
					 struct ieee80211_vif *vif,
					 u32 action)
{
	struct iwl_mac_ctx_cmd cmd = {};
	u32 tfd_queue_msk = BIT(mvm->snif_queue);
	int ret;

	WARN_ON(vif->type != NL80211_IFTYPE_MONITOR);

	iwl_mvm_mac_ctxt_cmd_common(mvm, vif, &cmd, NULL, action);

	cmd.filter_flags = cpu_to_le32(MAC_FILTER_IN_PROMISC |
				       MAC_FILTER_IN_CONTROL_AND_MGMT |
				       MAC_FILTER_IN_BEACON |
				       MAC_FILTER_IN_PROBE_REQUEST |
				       MAC_FILTER_IN_CRC32 |
				       MAC_FILTER_ACCEPT_GRP);
	ieee80211_hw_set(mvm->hw, RX_INCLUDES_FCS);

	/* Allocate sniffer station */
	ret = iwl_mvm_allocate_int_sta(mvm, &mvm->snif_sta, tfd_queue_msk,
				       vif->type, IWL_STA_GENERAL_PURPOSE);
	if (ret)
		return ret;

	return iwl_mvm_mac_ctxt_send_cmd(mvm, &cmd);
}