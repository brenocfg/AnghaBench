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
typedef  size_t u8 ;
struct sk_buff {scalar_t__ data; } ;
struct iwl_mvm_vif {int /*<<< orphan*/  ap_sta_id; } ;
struct iwl_mvm {int /*<<< orphan*/ * fw_id_to_mac_id; int /*<<< orphan*/  status; } ;
struct TYPE_3__ {TYPE_2__* vif; } ;
struct ieee80211_tx_info {int flags; TYPE_1__ control; } ;
struct ieee80211_tx_control {struct ieee80211_sta* sta; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_TX_OFFCHAN ; 
 scalar_t__ IS_ERR_OR_NULL (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  IWL_DEBUG_DROP (struct iwl_mvm*,char*) ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 size_t IWL_MVM_STATION_COUNT ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_ROC_AUX_RUNNING ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_ROC_RUNNING ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 size_t READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_is_bufferable_mmpdu (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_is_radio_killed (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_tx_skb (struct iwl_mvm*,struct sk_buff*,struct ieee80211_sta*) ; 
 scalar_t__ iwl_mvm_tx_skb_non_sta (struct iwl_mvm*,struct sk_buff*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (TYPE_2__*) ; 
 struct ieee80211_sta* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_mac_tx(struct ieee80211_hw *hw,
			   struct ieee80211_tx_control *control,
			   struct sk_buff *skb)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct ieee80211_sta *sta = control->sta;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_hdr *hdr = (void *)skb->data;
	bool offchannel = IEEE80211_SKB_CB(skb)->flags &
		IEEE80211_TX_CTL_TX_OFFCHAN;

	if (iwl_mvm_is_radio_killed(mvm)) {
		IWL_DEBUG_DROP(mvm, "Dropping - RF/CT KILL\n");
		goto drop;
	}

	if (offchannel &&
	    !test_bit(IWL_MVM_STATUS_ROC_RUNNING, &mvm->status) &&
	    !test_bit(IWL_MVM_STATUS_ROC_AUX_RUNNING, &mvm->status))
		goto drop;

	/* treat non-bufferable MMPDUs on AP interfaces as broadcast */
	if ((info->control.vif->type == NL80211_IFTYPE_AP ||
	     info->control.vif->type == NL80211_IFTYPE_ADHOC) &&
	    ieee80211_is_mgmt(hdr->frame_control) &&
	    !ieee80211_is_bufferable_mmpdu(hdr->frame_control))
		sta = NULL;

	/* If there is no sta, and it's not offchannel - send through AP */
	if (!sta && info->control.vif->type == NL80211_IFTYPE_STATION &&
	    !offchannel) {
		struct iwl_mvm_vif *mvmvif =
			iwl_mvm_vif_from_mac80211(info->control.vif);
		u8 ap_sta_id = READ_ONCE(mvmvif->ap_sta_id);

		if (ap_sta_id < IWL_MVM_STATION_COUNT) {
			/* mac80211 holds rcu read lock */
			sta = rcu_dereference(mvm->fw_id_to_mac_id[ap_sta_id]);
			if (IS_ERR_OR_NULL(sta))
				goto drop;
		}
	}

	if (sta) {
		if (iwl_mvm_tx_skb(mvm, skb, sta))
			goto drop;
		return;
	}

	if (iwl_mvm_tx_skb_non_sta(mvm, skb))
		goto drop;
	return;
 drop:
	ieee80211_free_txskb(hw, skb);
}