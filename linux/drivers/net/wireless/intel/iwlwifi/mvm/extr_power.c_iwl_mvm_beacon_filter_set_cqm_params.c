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
struct TYPE_4__ {int ba_enabled; } ;
struct iwl_mvm_vif {TYPE_2__ bf_data; } ;
struct iwl_mvm {int dummy; } ;
struct iwl_beacon_filter_cmd {void* ba_enable_beacon_abort; void* bf_roaming_state; void* bf_energy_delta; } ;
struct TYPE_3__ {int cqm_rssi_thold; int cqm_rssi_hyst; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;

/* Variables and functions */
 void* cpu_to_le32 (int) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static
void iwl_mvm_beacon_filter_set_cqm_params(struct iwl_mvm *mvm,
					  struct ieee80211_vif *vif,
					  struct iwl_beacon_filter_cmd *cmd)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);

	if (vif->bss_conf.cqm_rssi_thold) {
		cmd->bf_energy_delta =
			cpu_to_le32(vif->bss_conf.cqm_rssi_hyst);
		/* fw uses an absolute value for this */
		cmd->bf_roaming_state =
			cpu_to_le32(-vif->bss_conf.cqm_rssi_thold);
	}
	cmd->ba_enable_beacon_abort = cpu_to_le32(mvmvif->bf_data.ba_enabled);
}