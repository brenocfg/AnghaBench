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
struct iwl_sta_iter_data {int assoc; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_sta_iter_data*) ; 
 int /*<<< orphan*/  iwl_mvm_sta_iface_iterator ; 

bool iwl_mvm_is_vif_assoc(struct iwl_mvm *mvm)
{
	struct iwl_sta_iter_data data = {
		.assoc = false,
	};

	ieee80211_iterate_active_interfaces_atomic(mvm->hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   iwl_mvm_sta_iface_iterator,
						   &data);
	return data.assoc;
}