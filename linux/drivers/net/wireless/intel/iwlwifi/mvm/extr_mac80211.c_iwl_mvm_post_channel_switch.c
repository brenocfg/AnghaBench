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
struct iwl_mvm_vif {int csa_failed; int csa_bcn_pending; int ps_disabled; int /*<<< orphan*/  ap_sta_id; } ;
struct iwl_mvm_sta {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; TYPE_1__* fw; } ;
struct ieee80211_vif {scalar_t__ type; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int EIO ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_CHANNEL_SWITCH_CMD ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iwl_mvm_enable_beacon_filter (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_changed (struct iwl_mvm*,struct ieee80211_vif*,int,int /*<<< orphan*/ *) ; 
 int iwl_mvm_power_update_ps (struct iwl_mvm*) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_staid_protected (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_sta_modify_disable_tx (struct iwl_mvm*,struct iwl_mvm_sta*,int) ; 
 int /*<<< orphan*/  iwl_mvm_stop_session_protection (struct iwl_mvm*,struct ieee80211_vif*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_post_channel_switch(struct ieee80211_hw *hw,
				       struct ieee80211_vif *vif)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	int ret;

	mutex_lock(&mvm->mutex);

	if (mvmvif->csa_failed) {
		mvmvif->csa_failed = false;
		ret = -EIO;
		goto out_unlock;
	}

	if (vif->type == NL80211_IFTYPE_STATION) {
		struct iwl_mvm_sta *mvmsta;

		mvmvif->csa_bcn_pending = false;
		mvmsta = iwl_mvm_sta_from_staid_protected(mvm,
							  mvmvif->ap_sta_id);

		if (WARN_ON(!mvmsta)) {
			ret = -EIO;
			goto out_unlock;
		}

		if (!fw_has_capa(&mvm->fw->ucode_capa,
				 IWL_UCODE_TLV_CAPA_CHANNEL_SWITCH_CMD))
			iwl_mvm_sta_modify_disable_tx(mvm, mvmsta, false);

		iwl_mvm_mac_ctxt_changed(mvm, vif, false, NULL);

		if (!fw_has_capa(&mvm->fw->ucode_capa,
				 IWL_UCODE_TLV_CAPA_CHANNEL_SWITCH_CMD)) {
			ret = iwl_mvm_enable_beacon_filter(mvm, vif, 0);
			if (ret)
				goto out_unlock;

			iwl_mvm_stop_session_protection(mvm, vif);
		}
	}

	mvmvif->ps_disabled = false;

	ret = iwl_mvm_power_update_ps(mvm);

out_unlock:
	mutex_unlock(&mvm->mutex);

	return ret;
}