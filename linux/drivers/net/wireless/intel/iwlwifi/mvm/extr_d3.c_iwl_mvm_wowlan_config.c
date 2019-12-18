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
struct iwl_wowlan_config_cmd {int /*<<< orphan*/  offloading_tid; } ;
struct iwl_mvm_vif {int dummy; } ;
struct iwl_mvm {TYPE_1__* fw; int /*<<< orphan*/  mutex; int /*<<< orphan*/  offload_tid; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct cfg80211_wowlan {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  swcrypto; } ;
struct TYPE_3__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ASYNC ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_API_WOWLAN_TCP_SYN_WAKE ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_CNSLDTD_D3_D0_IMG ; 
 int /*<<< orphan*/  WOWLAN_CONFIGURATION ; 
 scalar_t__ fw_has_api (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iwl_mvm_d3_reprogram (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_sta*) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_wowlan_config_cmd*) ; 
 int iwl_mvm_send_patterns (struct iwl_mvm*,struct cfg80211_wowlan*) ; 
 int iwl_mvm_send_patterns_v1 (struct iwl_mvm*,struct cfg80211_wowlan*) ; 
 int iwl_mvm_send_proto_offload (struct iwl_mvm*,struct ieee80211_vif*,int,int,int /*<<< orphan*/ ) ; 
 int iwl_mvm_switch_to_d3 (struct iwl_mvm*) ; 
 int iwl_mvm_wowlan_config_key_params (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 TYPE_2__ iwlwifi_mod_params ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
iwl_mvm_wowlan_config(struct iwl_mvm *mvm,
		      struct cfg80211_wowlan *wowlan,
		      struct iwl_wowlan_config_cmd *wowlan_config_cmd,
		      struct ieee80211_vif *vif, struct iwl_mvm_vif *mvmvif,
		      struct ieee80211_sta *ap_sta)
{
	int ret;
	bool unified_image = fw_has_capa(&mvm->fw->ucode_capa,
					 IWL_UCODE_TLV_CAPA_CNSLDTD_D3_D0_IMG);

	mvm->offload_tid = wowlan_config_cmd->offloading_tid;

	if (!unified_image) {
		ret = iwl_mvm_switch_to_d3(mvm);
		if (ret)
			return ret;

		ret = iwl_mvm_d3_reprogram(mvm, vif, ap_sta);
		if (ret)
			return ret;
	}

	if (!iwlwifi_mod_params.swcrypto) {
		/*
		 * This needs to be unlocked due to lock ordering
		 * constraints. Since we're in the suspend path
		 * that isn't really a problem though.
		 */
		mutex_unlock(&mvm->mutex);
		ret = iwl_mvm_wowlan_config_key_params(mvm, vif, CMD_ASYNC);
		mutex_lock(&mvm->mutex);
		if (ret)
			return ret;
	}

	ret = iwl_mvm_send_cmd_pdu(mvm, WOWLAN_CONFIGURATION, 0,
				   sizeof(*wowlan_config_cmd),
				   wowlan_config_cmd);
	if (ret)
		return ret;

	if (fw_has_api(&mvm->fw->ucode_capa,
		       IWL_UCODE_TLV_API_WOWLAN_TCP_SYN_WAKE))
		ret = iwl_mvm_send_patterns(mvm, wowlan);
	else
		ret = iwl_mvm_send_patterns_v1(mvm, wowlan);
	if (ret)
		return ret;

	return iwl_mvm_send_proto_offload(mvm, vif, false, true, 0);
}