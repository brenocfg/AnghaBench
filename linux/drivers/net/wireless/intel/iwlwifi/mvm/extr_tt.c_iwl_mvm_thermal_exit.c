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
struct TYPE_2__ {int /*<<< orphan*/  ct_kill_exit; } ;
struct iwl_mvm {int init_status; TYPE_1__ thermal_throttle; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_TEMP (struct iwl_mvm*,char*) ; 
 int IWL_MVM_INIT_STATUS_THERMAL_INIT_COMPLETE ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_cooling_device_unregister (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_thermal_zone_unregister (struct iwl_mvm*) ; 

void iwl_mvm_thermal_exit(struct iwl_mvm *mvm)
{
	if (!(mvm->init_status & IWL_MVM_INIT_STATUS_THERMAL_INIT_COMPLETE))
		return;

	cancel_delayed_work_sync(&mvm->thermal_throttle.ct_kill_exit);
	IWL_DEBUG_TEMP(mvm, "Exit Thermal Throttling\n");

#ifdef CONFIG_THERMAL
	iwl_mvm_cooling_device_unregister(mvm);
	iwl_mvm_thermal_zone_unregister(mvm);
#endif
	mvm->init_status &= ~IWL_MVM_INIT_STATUS_THERMAL_INIT_COMPLETE;
}