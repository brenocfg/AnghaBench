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
struct iwl_mvm {int /*<<< orphan*/  aux_sta; int /*<<< orphan*/  aux_queue; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_MVM_TX_FIFO_MCAST ; 
 int /*<<< orphan*/  IWL_STA_AUX_ACTIVITY ; 
 int /*<<< orphan*/  MAC_INDEX_AUX ; 
 int /*<<< orphan*/  NL80211_IFTYPE_UNSPECIFIED ; 
 int iwl_mvm_add_int_sta_with_queue (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iwl_mvm_allocate_int_sta (struct iwl_mvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_dealloc_int_sta (struct iwl_mvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_add_aux_sta(struct iwl_mvm *mvm)
{
	int ret;

	lockdep_assert_held(&mvm->mutex);

	/* Allocate aux station and assign to it the aux queue */
	ret = iwl_mvm_allocate_int_sta(mvm, &mvm->aux_sta, BIT(mvm->aux_queue),
				       NL80211_IFTYPE_UNSPECIFIED,
				       IWL_STA_AUX_ACTIVITY);
	if (ret)
		return ret;

	ret = iwl_mvm_add_int_sta_with_queue(mvm, MAC_INDEX_AUX, 0,
					     &mvm->aux_sta, &mvm->aux_queue,
					     IWL_MVM_TX_FIFO_MCAST);
	if (ret) {
		iwl_mvm_dealloc_int_sta(mvm, &mvm->aux_sta);
		return ret;
	}

	return 0;
}