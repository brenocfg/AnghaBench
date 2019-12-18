#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t u8 ;
struct iwl_mvm_reorder_buffer {int /*<<< orphan*/  reorder_timer; int /*<<< orphan*/  lock; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  head_sn; } ;
struct iwl_mvm_delba_data {size_t baid; } ;
struct iwl_mvm_baid_data {size_t sta_id; struct iwl_mvm_reorder_buffer* reorder_buf; } ;
struct iwl_mvm {int /*<<< orphan*/ * fw_id_to_mac_id; int /*<<< orphan*/ * baid_map; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int IS_ERR_OR_NULL (struct ieee80211_sta*) ; 
 size_t IWL_MAX_BAID ; 
 scalar_t__ WARN_ONCE (int,char*,size_t) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_sn_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_release_frames (struct iwl_mvm*,struct ieee80211_sta*,int /*<<< orphan*/ *,struct iwl_mvm_baid_data*,struct iwl_mvm_reorder_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_del_ba(struct iwl_mvm *mvm, int queue,
			   struct iwl_mvm_delba_data *data)
{
	struct iwl_mvm_baid_data *ba_data;
	struct ieee80211_sta *sta;
	struct iwl_mvm_reorder_buffer *reorder_buf;
	u8 baid = data->baid;

	if (WARN_ONCE(baid >= IWL_MAX_BAID, "invalid BAID: %x\n", baid))
		return;

	rcu_read_lock();

	ba_data = rcu_dereference(mvm->baid_map[baid]);
	if (WARN_ON_ONCE(!ba_data))
		goto out;

	sta = rcu_dereference(mvm->fw_id_to_mac_id[ba_data->sta_id]);
	if (WARN_ON_ONCE(IS_ERR_OR_NULL(sta)))
		goto out;

	reorder_buf = &ba_data->reorder_buf[queue];

	/* release all frames that are in the reorder buffer to the stack */
	spin_lock_bh(&reorder_buf->lock);
	iwl_mvm_release_frames(mvm, sta, NULL, ba_data, reorder_buf,
			       ieee80211_sn_add(reorder_buf->head_sn,
						reorder_buf->buf_size),
			       0);
	spin_unlock_bh(&reorder_buf->lock);
	del_timer_sync(&reorder_buf->reorder_timer);

out:
	rcu_read_unlock();
}