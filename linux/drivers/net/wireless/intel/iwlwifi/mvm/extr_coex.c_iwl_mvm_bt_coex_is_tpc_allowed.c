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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  bt_activity_grading; } ;
struct iwl_mvm {TYPE_1__ last_bt_notif; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 scalar_t__ BT_LOW_TRAFFIC ; 
 int NL80211_BAND_2GHZ ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

bool iwl_mvm_bt_coex_is_tpc_allowed(struct iwl_mvm *mvm,
				    enum nl80211_band band)
{
	u32 bt_activity = le32_to_cpu(mvm->last_bt_notif.bt_activity_grading);

	if (band != NL80211_BAND_2GHZ)
		return false;

	return bt_activity >= BT_LOW_TRAFFIC;
}