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
typedef  int u8 ;
struct iwl_trans_txq_scd_cfg {scalar_t__ sta_id; int aggregate; int /*<<< orphan*/  frame_limit; int /*<<< orphan*/  tid; int /*<<< orphan*/  fifo; } ;
struct iwl_mvm_int_sta {scalar_t__ sta_id; int /*<<< orphan*/  tfd_queue_msk; } ;
struct iwl_mvm_vif {int /*<<< orphan*/  color; int /*<<< orphan*/  id; struct iwl_mvm_int_sta bcast_sta; } ;
struct iwl_mvm {int probe_queue; int p2p_dev_queue; int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int* bssid; } ;
struct ieee80211_vif {scalar_t__ type; TYPE_1__ bss_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  IWL_FRAME_LIMIT ; 
 int /*<<< orphan*/  IWL_MAX_TID_COUNT ; 
 scalar_t__ IWL_MVM_INVALID_STA ; 
 int /*<<< orphan*/  IWL_MVM_TX_FIFO_VO ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_P2P_DEVICE ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int iwl_mvm_add_int_sta_common (struct iwl_mvm*,struct iwl_mvm_int_sta*,int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_enable_txq (struct iwl_mvm*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct iwl_trans_txq_scd_cfg*,unsigned int) ; 
 unsigned int iwl_mvm_get_wd_timeout (struct iwl_mvm*,struct ieee80211_vif*,int,int) ; 
 scalar_t__ iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_rm_sta_common (struct iwl_mvm*,scalar_t__) ; 
 int iwl_mvm_tvqm_enable_txq (struct iwl_mvm*,scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_send_add_bcast_sta(struct iwl_mvm *mvm, struct ieee80211_vif *vif)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm_int_sta *bsta = &mvmvif->bcast_sta;
	static const u8 _baddr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	const u8 *baddr = _baddr;
	int queue;
	int ret;
	unsigned int wdg_timeout =
		iwl_mvm_get_wd_timeout(mvm, vif, false, false);
	struct iwl_trans_txq_scd_cfg cfg = {
		.fifo = IWL_MVM_TX_FIFO_VO,
		.sta_id = mvmvif->bcast_sta.sta_id,
		.tid = IWL_MAX_TID_COUNT,
		.aggregate = false,
		.frame_limit = IWL_FRAME_LIMIT,
	};

	lockdep_assert_held(&mvm->mutex);

	if (!iwl_mvm_has_new_tx_api(mvm)) {
		if (vif->type == NL80211_IFTYPE_AP ||
		    vif->type == NL80211_IFTYPE_ADHOC) {
			queue = mvm->probe_queue;
		} else if (vif->type == NL80211_IFTYPE_P2P_DEVICE) {
			queue = mvm->p2p_dev_queue;
		} else {
			WARN(1, "Missing required TXQ for adding bcast STA\n");
			return -EINVAL;
		}

		bsta->tfd_queue_msk |= BIT(queue);

		iwl_mvm_enable_txq(mvm, NULL, queue, 0, &cfg, wdg_timeout);
	}

	if (vif->type == NL80211_IFTYPE_ADHOC)
		baddr = vif->bss_conf.bssid;

	if (WARN_ON_ONCE(bsta->sta_id == IWL_MVM_INVALID_STA))
		return -ENOSPC;

	ret = iwl_mvm_add_int_sta_common(mvm, bsta, baddr,
					 mvmvif->id, mvmvif->color);
	if (ret)
		return ret;

	/*
	 * For 22000 firmware and on we cannot add queue to a station unknown
	 * to firmware so enable queue here - after the station was added
	 */
	if (iwl_mvm_has_new_tx_api(mvm)) {
		queue = iwl_mvm_tvqm_enable_txq(mvm, bsta->sta_id,
						IWL_MAX_TID_COUNT,
						wdg_timeout);
		if (queue < 0) {
			iwl_mvm_rm_sta_common(mvm, bsta->sta_id);
			return queue;
		}

		if (vif->type == NL80211_IFTYPE_AP ||
		    vif->type == NL80211_IFTYPE_ADHOC)
			mvm->probe_queue = queue;
		else if (vif->type == NL80211_IFTYPE_P2P_DEVICE)
			mvm->p2p_dev_queue = queue;
	}

	return 0;
}