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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm_tt_mgmt {int throttle; int dynamic_smps; int /*<<< orphan*/  ct_kill_exit; int /*<<< orphan*/  min_backoff; int /*<<< orphan*/  params; } ;
struct iwl_mvm {int /*<<< orphan*/  init_status; TYPE_1__* cfg; struct iwl_mvm_tt_mgmt thermal_throttle; } ;
struct TYPE_2__ {int /*<<< orphan*/ * thermal_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_DEBUG_TEMP (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_MVM_INIT_STATUS_THERMAL_INIT_COMPLETE ; 
 int /*<<< orphan*/  check_exit_ctkill ; 
 int /*<<< orphan*/  iwl_mvm_cooling_device_register (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_default_tt_params ; 
 int /*<<< orphan*/  iwl_mvm_thermal_zone_register (struct iwl_mvm*) ; 

void iwl_mvm_thermal_initialize(struct iwl_mvm *mvm, u32 min_backoff)
{
	struct iwl_mvm_tt_mgmt *tt = &mvm->thermal_throttle;

	IWL_DEBUG_TEMP(mvm, "Initialize Thermal Throttling\n");

	if (mvm->cfg->thermal_params)
		tt->params = *mvm->cfg->thermal_params;
	else
		tt->params = iwl_mvm_default_tt_params;

	tt->throttle = false;
	tt->dynamic_smps = false;
	tt->min_backoff = min_backoff;
	INIT_DELAYED_WORK(&tt->ct_kill_exit, check_exit_ctkill);

#ifdef CONFIG_THERMAL
	iwl_mvm_cooling_device_register(mvm);
	iwl_mvm_thermal_zone_register(mvm);
#endif
	mvm->init_status |= IWL_MVM_INIT_STATUS_THERMAL_INIT_COMPLETE;
}