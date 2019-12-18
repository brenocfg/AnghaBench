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
struct iwl_mvm_txq {int txq_id; } ;
struct iwl_mvm {TYPE_1__* queue_info; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_2__ {int tid_bitmap; size_t ra_sta_id; size_t txq_tid; int /*<<< orphan*/  mac80211_ac; } ;

/* Variables and functions */
 int BIT (size_t) ; 
 int /*<<< orphan*/  IEEE80211_AC_VO ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_mvm*,char*,int,int) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int,size_t) ; 
 size_t IWL_MAX_TID_COUNT ; 
 struct iwl_mvm_txq* iwl_mvm_txq_from_tid (struct ieee80211_sta*,size_t) ; 
 int /*<<< orphan*/ * tid_to_mac80211_ac ; 

__attribute__((used)) static bool iwl_mvm_update_txq_mapping(struct iwl_mvm *mvm,
				       struct ieee80211_sta *sta,
				       int queue, u8 sta_id, u8 tid)
{
	bool enable_queue = true;

	/* Make sure this TID isn't already enabled */
	if (mvm->queue_info[queue].tid_bitmap & BIT(tid)) {
		IWL_ERR(mvm, "Trying to enable TXQ %d with existing TID %d\n",
			queue, tid);
		return false;
	}

	/* Update mappings and refcounts */
	if (mvm->queue_info[queue].tid_bitmap)
		enable_queue = false;

	mvm->queue_info[queue].tid_bitmap |= BIT(tid);
	mvm->queue_info[queue].ra_sta_id = sta_id;

	if (enable_queue) {
		if (tid != IWL_MAX_TID_COUNT)
			mvm->queue_info[queue].mac80211_ac =
				tid_to_mac80211_ac[tid];
		else
			mvm->queue_info[queue].mac80211_ac = IEEE80211_AC_VO;

		mvm->queue_info[queue].txq_tid = tid;
	}

	if (sta) {
		struct iwl_mvm_txq *mvmtxq =
			iwl_mvm_txq_from_tid(sta, tid);

		mvmtxq->txq_id = queue;
	}

	IWL_DEBUG_TX_QUEUES(mvm,
			    "Enabling TXQ #%d tids=0x%x\n",
			    queue, mvm->queue_info[queue].tid_bitmap);

	return enable_queue;
}