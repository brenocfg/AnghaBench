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
typedef  int /*<<< orphan*/  u16 ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum ieee80211_frame_release_type { ____Placeholder_ieee80211_frame_release_type } ieee80211_frame_release_type ;

/* Variables and functions */
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  iwl_mvm_sta_modify_sleep_tx_count (struct iwl_mvm*,struct ieee80211_sta*,int,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
iwl_mvm_mac_release_buffered_frames(struct ieee80211_hw *hw,
				    struct ieee80211_sta *sta, u16 tids,
				    int num_frames,
				    enum ieee80211_frame_release_type reason,
				    bool more_data)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	/* Called when we need to transmit (a) frame(s) from agg or dqa queue */

	iwl_mvm_sta_modify_sleep_tx_count(mvm, sta, reason, num_frames,
					  tids, more_data, true);
}