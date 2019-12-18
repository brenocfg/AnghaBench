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
struct iwl_mvm_vif {struct iwl_mvm_phy_ctxt* phy_ctxt; } ;
struct iwl_mvm_phy_ctxt {scalar_t__ ref; struct ieee80211_channel* channel; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; struct iwl_mvm_phy_ctxt* phy_ctxts; TYPE_1__* fw; int /*<<< orphan*/  roc_done_wk; } ;
struct ieee80211_vif {int type; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_channel {int /*<<< orphan*/  hw_value; } ;
struct cfg80211_chan_def {int dummy; } ;
typedef  enum ieee80211_roc_type { ____Placeholder_ieee80211_roc_type } ieee80211_roc_type ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_mvm*,char*,...) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,...) ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_HOTSPOT_SUPPORT ; 
 int /*<<< orphan*/  NL80211_CHAN_NO_HT ; 
#define  NL80211_IFTYPE_P2P_DEVICE 129 
#define  NL80211_IFTYPE_STATION 128 
 int NUM_PHY_CTX ; 
 scalar_t__ WARN (int,char*) ; 
 int /*<<< orphan*/  cfg80211_chandef_create (struct cfg80211_chan_def*,struct ieee80211_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iwl_mvm_binding_add_vif (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_binding_remove_vif (struct iwl_mvm*,struct ieee80211_vif*) ; 
 struct iwl_mvm_phy_ctxt* iwl_mvm_get_free_phy_ctxt (struct iwl_mvm*) ; 
 int iwl_mvm_phy_ctxt_changed (struct iwl_mvm*,struct iwl_mvm_phy_ctxt*,struct cfg80211_chan_def*,int,int) ; 
 int /*<<< orphan*/  iwl_mvm_phy_ctxt_ref (struct iwl_mvm*,struct iwl_mvm_phy_ctxt*) ; 
 int /*<<< orphan*/  iwl_mvm_phy_ctxt_unref (struct iwl_mvm*,struct iwl_mvm_phy_ctxt*) ; 
 int iwl_mvm_send_aux_roc_cmd (struct iwl_mvm*,struct ieee80211_channel*,struct ieee80211_vif*,int) ; 
 int iwl_mvm_start_p2p_roc (struct iwl_mvm*,struct ieee80211_vif*,int,int) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_roc(struct ieee80211_hw *hw,
		       struct ieee80211_vif *vif,
		       struct ieee80211_channel *channel,
		       int duration,
		       enum ieee80211_roc_type type)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct cfg80211_chan_def chandef;
	struct iwl_mvm_phy_ctxt *phy_ctxt;
	int ret, i;

	IWL_DEBUG_MAC80211(mvm, "enter (%d, %d, %d)\n", channel->hw_value,
			   duration, type);

	/*
	 * Flush the done work, just in case it's still pending, so that
	 * the work it does can complete and we can accept new frames.
	 */
	flush_work(&mvm->roc_done_wk);

	mutex_lock(&mvm->mutex);

	switch (vif->type) {
	case NL80211_IFTYPE_STATION:
		if (fw_has_capa(&mvm->fw->ucode_capa,
				IWL_UCODE_TLV_CAPA_HOTSPOT_SUPPORT)) {
			/* Use aux roc framework (HS20) */
			ret = iwl_mvm_send_aux_roc_cmd(mvm, channel,
						       vif, duration);
			goto out_unlock;
		}
		IWL_ERR(mvm, "hotspot not supported\n");
		ret = -EINVAL;
		goto out_unlock;
	case NL80211_IFTYPE_P2P_DEVICE:
		/* handle below */
		break;
	default:
		IWL_ERR(mvm, "vif isn't P2P_DEVICE: %d\n", vif->type);
		ret = -EINVAL;
		goto out_unlock;
	}

	for (i = 0; i < NUM_PHY_CTX; i++) {
		phy_ctxt = &mvm->phy_ctxts[i];
		if (phy_ctxt->ref == 0 || mvmvif->phy_ctxt == phy_ctxt)
			continue;

		if (phy_ctxt->ref && channel == phy_ctxt->channel) {
			/*
			 * Unbind the P2P_DEVICE from the current PHY context,
			 * and if the PHY context is not used remove it.
			 */
			ret = iwl_mvm_binding_remove_vif(mvm, vif);
			if (WARN(ret, "Failed unbinding P2P_DEVICE\n"))
				goto out_unlock;

			iwl_mvm_phy_ctxt_unref(mvm, mvmvif->phy_ctxt);

			/* Bind the P2P_DEVICE to the current PHY Context */
			mvmvif->phy_ctxt = phy_ctxt;

			ret = iwl_mvm_binding_add_vif(mvm, vif);
			if (WARN(ret, "Failed binding P2P_DEVICE\n"))
				goto out_unlock;

			iwl_mvm_phy_ctxt_ref(mvm, mvmvif->phy_ctxt);
			goto schedule_time_event;
		}
	}

	/* Need to update the PHY context only if the ROC channel changed */
	if (channel == mvmvif->phy_ctxt->channel)
		goto schedule_time_event;

	cfg80211_chandef_create(&chandef, channel, NL80211_CHAN_NO_HT);

	/*
	 * Change the PHY context configuration as it is currently referenced
	 * only by the P2P Device MAC
	 */
	if (mvmvif->phy_ctxt->ref == 1) {
		ret = iwl_mvm_phy_ctxt_changed(mvm, mvmvif->phy_ctxt,
					       &chandef, 1, 1);
		if (ret)
			goto out_unlock;
	} else {
		/*
		 * The PHY context is shared with other MACs. Need to remove the
		 * P2P Device from the binding, allocate an new PHY context and
		 * create a new binding
		 */
		phy_ctxt = iwl_mvm_get_free_phy_ctxt(mvm);
		if (!phy_ctxt) {
			ret = -ENOSPC;
			goto out_unlock;
		}

		ret = iwl_mvm_phy_ctxt_changed(mvm, phy_ctxt, &chandef,
					       1, 1);
		if (ret) {
			IWL_ERR(mvm, "Failed to change PHY context\n");
			goto out_unlock;
		}

		/* Unbind the P2P_DEVICE from the current PHY context */
		ret = iwl_mvm_binding_remove_vif(mvm, vif);
		if (WARN(ret, "Failed unbinding P2P_DEVICE\n"))
			goto out_unlock;

		iwl_mvm_phy_ctxt_unref(mvm, mvmvif->phy_ctxt);

		/* Bind the P2P_DEVICE to the new allocated PHY context */
		mvmvif->phy_ctxt = phy_ctxt;

		ret = iwl_mvm_binding_add_vif(mvm, vif);
		if (WARN(ret, "Failed binding P2P_DEVICE\n"))
			goto out_unlock;

		iwl_mvm_phy_ctxt_ref(mvm, mvmvif->phy_ctxt);
	}

schedule_time_event:
	/* Schedule the time events */
	ret = iwl_mvm_start_p2p_roc(mvm, vif, duration, type);

out_unlock:
	mutex_unlock(&mvm->mutex);
	IWL_DEBUG_MAC80211(mvm, "leave\n");
	return ret;
}