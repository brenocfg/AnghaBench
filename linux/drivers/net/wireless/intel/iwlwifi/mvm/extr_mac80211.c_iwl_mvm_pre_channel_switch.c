#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct iwl_mvm_vif {int csa_failed; int csa_countdown; int csa_count; int csa_misbehave; int ps_disabled; int /*<<< orphan*/  csa_work; int /*<<< orphan*/  csa_target_freq; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; TYPE_4__* fw; int /*<<< orphan*/  csa_vif; int /*<<< orphan*/  csa_tx_blocked_vif; int /*<<< orphan*/  fwrt; } ;
struct TYPE_7__ {int beacon_int; } ;
struct ieee80211_vif {int type; TYPE_3__ bss_conf; int /*<<< orphan*/  csa_active; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_6__ {TYPE_1__* chan; int /*<<< orphan*/  center_freq1; } ;
struct ieee80211_channel_switch {int count; int /*<<< orphan*/  block_tx; TYPE_2__ chandef; } ;
struct TYPE_8__ {int /*<<< orphan*/  ucode_capa; } ;
struct TYPE_5__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  FW_DBG_TRIGGER_CHANNEL_SWITCH ; 
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_mvm*,char*,int /*<<< orphan*/ ) ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int IWL_MAX_CSA_BLOCK_TX ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_CHANNEL_SWITCH_CMD ; 
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_vif_to_wdev (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_fw_dbg_trigger_simple_stop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_mvm_old_pre_chan_sw_sta (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_channel_switch*) ; 
 int iwl_mvm_power_update_ps (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_schedule_client_csa (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_channel_switch*) ; 
 int /*<<< orphan*/  iwl_mvm_teardown_tdls_peers (struct iwl_mvm*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ieee80211_vif*) ; 
 struct ieee80211_vif* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_mvm_pre_channel_switch(struct ieee80211_hw *hw,
				      struct ieee80211_vif *vif,
				      struct ieee80211_channel_switch *chsw)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct ieee80211_vif *csa_vif;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	int ret;

	mutex_lock(&mvm->mutex);

	mvmvif->csa_failed = false;

	IWL_DEBUG_MAC80211(mvm, "pre CSA to freq %d\n",
			   chsw->chandef.center_freq1);

	iwl_fw_dbg_trigger_simple_stop(&mvm->fwrt,
				       ieee80211_vif_to_wdev(vif),
				       FW_DBG_TRIGGER_CHANNEL_SWITCH);

	switch (vif->type) {
	case NL80211_IFTYPE_AP:
		csa_vif =
			rcu_dereference_protected(mvm->csa_vif,
						  lockdep_is_held(&mvm->mutex));
		if (WARN_ONCE(csa_vif && csa_vif->csa_active,
			      "Another CSA is already in progress")) {
			ret = -EBUSY;
			goto out_unlock;
		}

		/* we still didn't unblock tx. prevent new CS meanwhile */
		if (rcu_dereference_protected(mvm->csa_tx_blocked_vif,
					      lockdep_is_held(&mvm->mutex))) {
			ret = -EBUSY;
			goto out_unlock;
		}

		rcu_assign_pointer(mvm->csa_vif, vif);

		if (WARN_ONCE(mvmvif->csa_countdown,
			      "Previous CSA countdown didn't complete")) {
			ret = -EBUSY;
			goto out_unlock;
		}

		mvmvif->csa_target_freq = chsw->chandef.chan->center_freq;

		break;
	case NL80211_IFTYPE_STATION:
		if (chsw->block_tx) {
			/*
			 * In case of undetermined / long time with immediate
			 * quiet monitor status to gracefully disconnect
			 */
			if (!chsw->count ||
			    chsw->count * vif->bss_conf.beacon_int >
			    IWL_MAX_CSA_BLOCK_TX)
				schedule_delayed_work(&mvmvif->csa_work,
						      msecs_to_jiffies(IWL_MAX_CSA_BLOCK_TX));
		}

		if (!fw_has_capa(&mvm->fw->ucode_capa,
				 IWL_UCODE_TLV_CAPA_CHANNEL_SWITCH_CMD)) {
			ret = iwl_mvm_old_pre_chan_sw_sta(mvm, vif, chsw);
			if (ret)
				goto out_unlock;
		} else {
			iwl_mvm_schedule_client_csa(mvm, vif, chsw);
		}

		mvmvif->csa_count = chsw->count;
		mvmvif->csa_misbehave = false;
		break;
	default:
		break;
	}

	mvmvif->ps_disabled = true;

	ret = iwl_mvm_power_update_ps(mvm);
	if (ret)
		goto out_unlock;

	/* we won't be on this channel any longer */
	iwl_mvm_teardown_tdls_peers(mvm);

out_unlock:
	mutex_unlock(&mvm->mutex);

	return ret;
}