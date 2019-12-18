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
struct iwl_mvm {int /*<<< orphan*/  hw; TYPE_1__* cfg; int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {scalar_t__ rx_with_siso_diversity; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  iwl_mvm_diversity_iter ; 
 int /*<<< orphan*/  iwl_mvm_get_valid_rx_ant (struct iwl_mvm*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int num_of_ant (int /*<<< orphan*/ ) ; 

bool iwl_mvm_rx_diversity_allowed(struct iwl_mvm *mvm)
{
	bool result = true;

	lockdep_assert_held(&mvm->mutex);

	if (num_of_ant(iwl_mvm_get_valid_rx_ant(mvm)) == 1)
		return false;

	if (mvm->cfg->rx_with_siso_diversity)
		return false;

	ieee80211_iterate_active_interfaces_atomic(
			mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
			iwl_mvm_diversity_iter, &result);

	return result;
}