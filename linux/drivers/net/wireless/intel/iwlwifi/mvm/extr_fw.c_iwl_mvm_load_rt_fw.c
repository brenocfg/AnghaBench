#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cur_fw_img; } ;
struct iwl_mvm {int rfkill_safe_init_done; TYPE_2__ fwrt; int /*<<< orphan*/  trans; } ;
struct TYPE_5__ {scalar_t__ init_dbg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_FW_INI_TIME_POINT_AFTER_ALIVE ; 
 int /*<<< orphan*/  IWL_FW_INI_TIME_POINT_EARLY ; 
 int /*<<< orphan*/  IWL_UCODE_REGULAR ; 
 int /*<<< orphan*/  iwl_dbg_tlv_time_point (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_fw_dbg_stop_sync (TYPE_2__*) ; 
 int iwl_init_paging (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_has_unified_ucode (struct iwl_mvm*) ; 
 int iwl_mvm_load_ucode_wait_alive (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int iwl_run_init_mvm_ucode (struct iwl_mvm*,int) ; 
 int iwl_run_unified_mvm_ucode (struct iwl_mvm*,int) ; 
 int iwl_trans_start_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_stop_device (int /*<<< orphan*/ ) ; 
 TYPE_1__ iwlmvm_mod_params ; 

__attribute__((used)) static int iwl_mvm_load_rt_fw(struct iwl_mvm *mvm)
{
	int ret;

	if (iwl_mvm_has_unified_ucode(mvm))
		return iwl_run_unified_mvm_ucode(mvm, false);

	ret = iwl_run_init_mvm_ucode(mvm, false);

	if (ret) {
		IWL_ERR(mvm, "Failed to run INIT ucode: %d\n", ret);

		if (iwlmvm_mod_params.init_dbg)
			return 0;
		return ret;
	}

	iwl_fw_dbg_stop_sync(&mvm->fwrt);
	iwl_trans_stop_device(mvm->trans);
	ret = iwl_trans_start_hw(mvm->trans);
	if (ret)
		return ret;

	iwl_dbg_tlv_time_point(&mvm->fwrt, IWL_FW_INI_TIME_POINT_EARLY, NULL);

	mvm->rfkill_safe_init_done = false;
	ret = iwl_mvm_load_ucode_wait_alive(mvm, IWL_UCODE_REGULAR);
	if (ret)
		return ret;

	mvm->rfkill_safe_init_done = true;

	iwl_dbg_tlv_time_point(&mvm->fwrt, IWL_FW_INI_TIME_POINT_AFTER_ALIVE,
			       NULL);

	return iwl_init_paging(&mvm->fwrt, mvm->fwrt.cur_fw_img);
}