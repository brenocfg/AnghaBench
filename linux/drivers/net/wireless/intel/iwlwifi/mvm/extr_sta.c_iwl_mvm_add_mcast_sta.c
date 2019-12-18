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
struct iwl_trans_txq_scd_cfg {int aggregate; int /*<<< orphan*/  frame_limit; int /*<<< orphan*/  tid; int /*<<< orphan*/  sta_id; int /*<<< orphan*/  fifo; } ;
struct iwl_mvm_int_sta {int /*<<< orphan*/  sta_id; int /*<<< orphan*/  tfd_queue_msk; } ;
struct iwl_mvm_vif {int cab_queue; int /*<<< orphan*/  color; int /*<<< orphan*/  id; struct iwl_mvm_int_sta mcast_sta; } ;
struct iwl_mvm {TYPE_1__* fw; int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {scalar_t__ type; } ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  IWL_FRAME_LIMIT ; 
 int IWL_MVM_DQA_GCAST_QUEUE ; 
 int /*<<< orphan*/  IWL_MVM_TX_FIFO_BE ; 
 int /*<<< orphan*/  IWL_MVM_TX_FIFO_MCAST ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_API_STA_TYPE ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ fw_has_api (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iwl_mvm_add_int_sta_common (struct iwl_mvm*,struct iwl_mvm_int_sta*,int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_dealloc_int_sta (struct iwl_mvm*,struct iwl_mvm_int_sta*) ; 
 int /*<<< orphan*/  iwl_mvm_enable_txq (struct iwl_mvm*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct iwl_trans_txq_scd_cfg*,unsigned int) ; 
 unsigned int iwl_mvm_get_wd_timeout (struct iwl_mvm*,struct ieee80211_vif*,int,int) ; 
 scalar_t__ iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int iwl_mvm_tvqm_enable_txq (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_add_mcast_sta(struct iwl_mvm *mvm, struct ieee80211_vif *vif)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm_int_sta *msta = &mvmvif->mcast_sta;
	static const u8 _maddr[] = {0x03, 0x00, 0x00, 0x00, 0x00, 0x00};
	const u8 *maddr = _maddr;
	struct iwl_trans_txq_scd_cfg cfg = {
		.fifo = vif->type == NL80211_IFTYPE_AP ?
			IWL_MVM_TX_FIFO_MCAST : IWL_MVM_TX_FIFO_BE,
		.sta_id = msta->sta_id,
		.tid = 0,
		.aggregate = false,
		.frame_limit = IWL_FRAME_LIMIT,
	};
	unsigned int timeout = iwl_mvm_get_wd_timeout(mvm, vif, false, false);
	int ret;

	lockdep_assert_held(&mvm->mutex);

	if (WARN_ON(vif->type != NL80211_IFTYPE_AP &&
		    vif->type != NL80211_IFTYPE_ADHOC))
		return -ENOTSUPP;

	/*
	 * In IBSS, ieee80211_check_queues() sets the cab_queue to be
	 * invalid, so make sure we use the queue we want.
	 * Note that this is done here as we want to avoid making DQA
	 * changes in mac80211 layer.
	 */
	if (vif->type == NL80211_IFTYPE_ADHOC)
		mvmvif->cab_queue = IWL_MVM_DQA_GCAST_QUEUE;

	/*
	 * While in previous FWs we had to exclude cab queue from TFD queue
	 * mask, now it is needed as any other queue.
	 */
	if (!iwl_mvm_has_new_tx_api(mvm) &&
	    fw_has_api(&mvm->fw->ucode_capa, IWL_UCODE_TLV_API_STA_TYPE)) {
		iwl_mvm_enable_txq(mvm, NULL, mvmvif->cab_queue, 0, &cfg,
				   timeout);
		msta->tfd_queue_msk |= BIT(mvmvif->cab_queue);
	}
	ret = iwl_mvm_add_int_sta_common(mvm, msta, maddr,
					 mvmvif->id, mvmvif->color);
	if (ret)
		goto err;

	/*
	 * Enable cab queue after the ADD_STA command is sent.
	 * This is needed for 22000 firmware which won't accept SCD_QUEUE_CFG
	 * command with unknown station id, and for FW that doesn't support
	 * station API since the cab queue is not included in the
	 * tfd_queue_mask.
	 */
	if (iwl_mvm_has_new_tx_api(mvm)) {
		int queue = iwl_mvm_tvqm_enable_txq(mvm, msta->sta_id,
						    0,
						    timeout);
		if (queue < 0) {
			ret = queue;
			goto err;
		}
		mvmvif->cab_queue = queue;
	} else if (!fw_has_api(&mvm->fw->ucode_capa,
			       IWL_UCODE_TLV_API_STA_TYPE))
		iwl_mvm_enable_txq(mvm, NULL, mvmvif->cab_queue, 0, &cfg,
				   timeout);

	return 0;
err:
	iwl_mvm_dealloc_int_sta(mvm, msta);
	return ret;
}