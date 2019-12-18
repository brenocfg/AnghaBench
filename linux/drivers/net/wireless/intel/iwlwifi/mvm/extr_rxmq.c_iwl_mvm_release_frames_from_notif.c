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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct napi_struct {int dummy; } ;
struct iwl_mvm_reorder_buffer {int /*<<< orphan*/  lock; } ;
struct iwl_mvm_baid_data {size_t sta_id; struct iwl_mvm_reorder_buffer* reorder_buf; } ;
struct iwl_mvm {int /*<<< orphan*/ * fw_id_to_mac_id; int /*<<< orphan*/ * baid_map; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int IS_ERR_OR_NULL (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  IWL_DEBUG_HT (struct iwl_mvm*,char*,size_t,int /*<<< orphan*/ ) ; 
 size_t IWL_RX_REORDER_DATA_INVALID_BAID ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  iwl_mvm_release_frames (struct iwl_mvm*,struct ieee80211_sta*,struct napi_struct*,struct iwl_mvm_baid_data*,struct iwl_mvm_reorder_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_release_frames_from_notif(struct iwl_mvm *mvm,
					      struct napi_struct *napi,
					      u8 baid, u16 nssn, int queue,
					      u32 flags)
{
	struct ieee80211_sta *sta;
	struct iwl_mvm_reorder_buffer *reorder_buf;
	struct iwl_mvm_baid_data *ba_data;

	IWL_DEBUG_HT(mvm, "Frame release notification for BAID %u, NSSN %d\n",
		     baid, nssn);

	if (WARN_ON_ONCE(baid == IWL_RX_REORDER_DATA_INVALID_BAID ||
			 baid >= ARRAY_SIZE(mvm->baid_map)))
		return;

	rcu_read_lock();

	ba_data = rcu_dereference(mvm->baid_map[baid]);
	if (WARN_ON_ONCE(!ba_data))
		goto out;

	sta = rcu_dereference(mvm->fw_id_to_mac_id[ba_data->sta_id]);
	if (WARN_ON_ONCE(IS_ERR_OR_NULL(sta)))
		goto out;

	reorder_buf = &ba_data->reorder_buf[queue];

	spin_lock_bh(&reorder_buf->lock);
	iwl_mvm_release_frames(mvm, sta, napi, ba_data,
			       reorder_buf, nssn, flags);
	spin_unlock_bh(&reorder_buf->lock);

out:
	rcu_read_unlock();
}