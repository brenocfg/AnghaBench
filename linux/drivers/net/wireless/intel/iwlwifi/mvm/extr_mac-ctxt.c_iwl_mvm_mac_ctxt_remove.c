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
struct iwl_mvm_vif {int uploaded; int /*<<< orphan*/  color; int /*<<< orphan*/  id; } ;
struct iwl_mvm {TYPE_1__* hw; } ;
struct iwl_mac_ctx_cmd {void* action; void* id_and_color; } ;
struct ieee80211_vif {scalar_t__ type; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FW_CMD_ID_AND_COLOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_CTXT_ACTION_REMOVE ; 
 int /*<<< orphan*/  IEEE80211_HW_RX_INCLUDES_FCS ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  MAC_CONTEXT_CMD ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 scalar_t__ WARN_ONCE (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_vif_type_p2p (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_dealloc_snif_sta (struct iwl_mvm*) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_mac_ctx_cmd*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  memset (struct iwl_mac_ctx_cmd*,int /*<<< orphan*/ ,int) ; 

int iwl_mvm_mac_ctxt_remove(struct iwl_mvm *mvm, struct ieee80211_vif *vif)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mac_ctx_cmd cmd;
	int ret;

	if (WARN_ONCE(!mvmvif->uploaded, "Removing inactive MAC %pM/%d\n",
		      vif->addr, ieee80211_vif_type_p2p(vif)))
		return -EIO;

	memset(&cmd, 0, sizeof(cmd));

	cmd.id_and_color = cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvif->id,
							   mvmvif->color));
	cmd.action = cpu_to_le32(FW_CTXT_ACTION_REMOVE);

	ret = iwl_mvm_send_cmd_pdu(mvm, MAC_CONTEXT_CMD, 0,
				   sizeof(cmd), &cmd);
	if (ret) {
		IWL_ERR(mvm, "Failed to remove MAC context: %d\n", ret);
		return ret;
	}

	mvmvif->uploaded = false;

	if (vif->type == NL80211_IFTYPE_MONITOR) {
		__clear_bit(IEEE80211_HW_RX_INCLUDES_FCS, mvm->hw->flags);
		iwl_mvm_dealloc_snif_sta(mvm);
	}

	return 0;
}