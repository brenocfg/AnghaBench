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
struct iwl_mvm_mc_iter_data {struct iwl_mvm* mvm; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; int /*<<< orphan*/  mcast_filter_cmd; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_mvm_mc_iter_data*) ; 
 int /*<<< orphan*/  iwl_mvm_mc_iface_iterator ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_recalc_multicast(struct iwl_mvm *mvm)
{
	struct iwl_mvm_mc_iter_data iter_data = {
		.mvm = mvm,
	};

	lockdep_assert_held(&mvm->mutex);

	if (WARN_ON_ONCE(!mvm->mcast_filter_cmd))
		return;

	ieee80211_iterate_active_interfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
		iwl_mvm_mc_iface_iterator, &iter_data);
}