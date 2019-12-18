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
struct iwl_mvm {int dummy; } ;
struct iwl_lq_sta {int /*<<< orphan*/  stbc_capable; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_mvm_bt_coex_is_mimo_allowed (struct iwl_mvm*,struct ieee80211_sta*) ; 

__attribute__((used)) static bool rs_stbc_allow(struct iwl_mvm *mvm, struct ieee80211_sta *sta,
			  struct iwl_lq_sta *lq_sta)
{
	/* Our chip supports Tx STBC and the peer is an HT/VHT STA which
	 * supports STBC of at least 1*SS
	 */
	if (!lq_sta->stbc_capable)
		return false;

	if (!iwl_mvm_bt_coex_is_mimo_allowed(mvm, sta))
		return false;

	return true;
}