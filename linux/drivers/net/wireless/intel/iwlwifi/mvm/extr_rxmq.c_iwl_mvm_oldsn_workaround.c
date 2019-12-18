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
typedef  scalar_t__ u32 ;
struct iwl_mvm_sta {int /*<<< orphan*/  vif; } ;
struct iwl_mvm_reorder_buffer {scalar_t__ consec_oldsn_ampdu_gp2; int consec_oldsn_prev_drop; scalar_t__ consec_oldsn_drops; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ IWL_MVM_AMPDU_CONSEC_DROPS_DELBA ; 
 scalar_t__ IWL_RX_MPDU_REORDER_BA_OLD_SN ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_mvm*,char*,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ieee80211_stop_rx_ba_session (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 

__attribute__((used)) static void iwl_mvm_oldsn_workaround(struct iwl_mvm *mvm,
				     struct ieee80211_sta *sta, int tid,
				     struct iwl_mvm_reorder_buffer *buffer,
				     u32 reorder, u32 gp2, int queue)
{
	struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);

	if (gp2 != buffer->consec_oldsn_ampdu_gp2) {
		/* we have a new (A-)MPDU ... */

		/*
		 * reset counter to 0 if we didn't have any oldsn in
		 * the last A-MPDU (as detected by GP2 being identical)
		 */
		if (!buffer->consec_oldsn_prev_drop)
			buffer->consec_oldsn_drops = 0;

		/* either way, update our tracking state */
		buffer->consec_oldsn_ampdu_gp2 = gp2;
	} else if (buffer->consec_oldsn_prev_drop) {
		/*
		 * tracking state didn't change, and we had an old SN
		 * indication before - do nothing in this case, we
		 * already noted this one down and are waiting for the
		 * next A-MPDU (by GP2)
		 */
		return;
	}

	/* return unless this MPDU has old SN */
	if (!(reorder & IWL_RX_MPDU_REORDER_BA_OLD_SN))
		return;

	/* update state */
	buffer->consec_oldsn_prev_drop = 1;
	buffer->consec_oldsn_drops++;

	/* if limit is reached, send del BA and reset state */
	if (buffer->consec_oldsn_drops == IWL_MVM_AMPDU_CONSEC_DROPS_DELBA) {
		IWL_WARN(mvm,
			 "reached %d old SN frames from %pM on queue %d, stopping BA session on TID %d\n",
			 IWL_MVM_AMPDU_CONSEC_DROPS_DELBA,
			 sta->addr, queue, tid);
		ieee80211_stop_rx_ba_session(mvmsta->vif, BIT(tid), sta->addr);
		buffer->consec_oldsn_prev_drop = 0;
		buffer->consec_oldsn_drops = 0;
	}
}