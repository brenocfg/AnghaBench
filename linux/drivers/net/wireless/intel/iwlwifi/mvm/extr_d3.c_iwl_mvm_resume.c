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
struct iwl_mvm {int /*<<< orphan*/  fwrt; TYPE_1__* trans; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  system_pm_mode; } ;

/* Variables and functions */
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  IWL_PLAT_PM_MODE_DISABLED ; 
 int /*<<< orphan*/  iwl_fw_runtime_resume (int /*<<< orphan*/ *) ; 
 int iwl_mvm_resume_d3 (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_resume_tcm (struct iwl_mvm*) ; 

int iwl_mvm_resume(struct ieee80211_hw *hw)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	int ret;

	ret = iwl_mvm_resume_d3(mvm);

	mvm->trans->system_pm_mode = IWL_PLAT_PM_MODE_DISABLED;

	iwl_mvm_resume_tcm(mvm);

	iwl_fw_runtime_resume(&mvm->fwrt);

	return ret;
}