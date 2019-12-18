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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm_sta {unsigned long tid_disable_agg; int /*<<< orphan*/  tfd_queue_msk; int /*<<< orphan*/  sta_id; int /*<<< orphan*/  mac_id_n_color; } ;
struct iwl_mvm_add_sta_cmd {int /*<<< orphan*/  tid_disable_tx; void* tfd_queue_msk; int /*<<< orphan*/  modify_mask; int /*<<< orphan*/  add_modify; int /*<<< orphan*/  sta_id; void* mac_id_n_color; } ;
struct iwl_mvm {int /*<<< orphan*/ * fw_id_to_mac_id; TYPE_1__* queue_info; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_2__ {size_t ra_sta_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_STA ; 
 int /*<<< orphan*/  ADD_STA_SUCCESS ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  STA_MODE_MODIFY ; 
 int /*<<< orphan*/  STA_MODIFY_QUEUES ; 
 int /*<<< orphan*/  STA_MODIFY_QUEUE_REMOVAL ; 
 int /*<<< orphan*/  STA_MODIFY_TID_DISABLE_TX ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned long) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_add_sta_cmd_size (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int iwl_mvm_send_cmd_pdu_status (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_mvm_add_sta_cmd*,int /*<<< orphan*/ *) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 struct ieee80211_sta* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int iwl_mvm_invalidate_sta_queue(struct iwl_mvm *mvm, int queue,
					unsigned long disable_agg_tids,
					bool remove_queue)
{
	struct iwl_mvm_add_sta_cmd cmd = {};
	struct ieee80211_sta *sta;
	struct iwl_mvm_sta *mvmsta;
	u32 status;
	u8 sta_id;

	if (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		return -EINVAL;

	sta_id = mvm->queue_info[queue].ra_sta_id;

	rcu_read_lock();

	sta = rcu_dereference(mvm->fw_id_to_mac_id[sta_id]);

	if (WARN_ON_ONCE(IS_ERR_OR_NULL(sta))) {
		rcu_read_unlock();
		return -EINVAL;
	}

	mvmsta = iwl_mvm_sta_from_mac80211(sta);

	mvmsta->tid_disable_agg |= disable_agg_tids;

	cmd.mac_id_n_color = cpu_to_le32(mvmsta->mac_id_n_color);
	cmd.sta_id = mvmsta->sta_id;
	cmd.add_modify = STA_MODE_MODIFY;
	cmd.modify_mask = STA_MODIFY_QUEUES;
	if (disable_agg_tids)
		cmd.modify_mask |= STA_MODIFY_TID_DISABLE_TX;
	if (remove_queue)
		cmd.modify_mask |= STA_MODIFY_QUEUE_REMOVAL;
	cmd.tfd_queue_msk = cpu_to_le32(mvmsta->tfd_queue_msk);
	cmd.tid_disable_tx = cpu_to_le16(mvmsta->tid_disable_agg);

	rcu_read_unlock();

	/* Notify FW of queue removal from the STA queues */
	status = ADD_STA_SUCCESS;
	return iwl_mvm_send_cmd_pdu_status(mvm, ADD_STA,
					   iwl_mvm_add_sta_cmd_size(mvm),
					   &cmd, &status);
}