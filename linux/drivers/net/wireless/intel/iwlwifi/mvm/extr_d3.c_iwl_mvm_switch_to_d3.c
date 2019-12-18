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
struct iwl_mvm {scalar_t__ ptk_icvlen; scalar_t__ ptk_ivlen; int /*<<< orphan*/  fw_key_table; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_MVM_SCAN_REGULAR ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_HW_RESTART ; 
 int iwl_mvm_load_d3_fw (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_scan_stop (struct iwl_mvm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_mvm_stop_device (struct iwl_mvm*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_switch_to_d3(struct iwl_mvm *mvm)
{
	iwl_mvm_scan_stop(mvm, IWL_MVM_SCAN_REGULAR, true);

	iwl_mvm_stop_device(mvm);
	/*
	 * Set the HW restart bit -- this is mostly true as we're
	 * going to load new firmware and reprogram that, though
	 * the reprogramming is going to be manual to avoid adding
	 * all the MACs that aren't support.
	 * We don't have to clear up everything though because the
	 * reprogramming is manual. When we resume, we'll actually
	 * go through a proper restart sequence again to switch
	 * back to the runtime firmware image.
	 */
	set_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status);

	/* the fw is reset, so all the keys are cleared */
	memset(mvm->fw_key_table, 0, sizeof(mvm->fw_key_table));

	mvm->ptk_ivlen = 0;
	mvm->ptk_icvlen = 0;
	mvm->ptk_ivlen = 0;
	mvm->ptk_icvlen = 0;

	return iwl_mvm_load_d3_fw(mvm);
}