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
struct iwl_op_mode {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/  notif_wait; int /*<<< orphan*/  status; int /*<<< orphan*/  rfkill_safe_init_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_MVM_STATUS_HW_RFKILL ; 
 struct iwl_mvm* IWL_OP_MODE_GET_MVM (struct iwl_op_mode*) ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_abort_notification_waits (int /*<<< orphan*/ *) ; 
 int iwl_mvm_has_unified_ucode (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_set_rfkill_state (struct iwl_mvm*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool iwl_mvm_set_hw_rfkill_state(struct iwl_op_mode *op_mode, bool state)
{
	struct iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);
	bool rfkill_safe_init_done = READ_ONCE(mvm->rfkill_safe_init_done);
	bool unified = iwl_mvm_has_unified_ucode(mvm);

	if (state)
		set_bit(IWL_MVM_STATUS_HW_RFKILL, &mvm->status);
	else
		clear_bit(IWL_MVM_STATUS_HW_RFKILL, &mvm->status);

	iwl_mvm_set_rfkill_state(mvm);

	 /* iwl_run_init_mvm_ucode is waiting for results, abort it. */
	if (rfkill_safe_init_done)
		iwl_abort_notification_waits(&mvm->notif_wait);

	/*
	 * Don't ask the transport to stop the firmware. We'll do it
	 * after cfg80211 takes us down.
	 */
	if (unified)
		return false;

	/*
	 * Stop the device if we run OPERATIONAL firmware or if we are in the
	 * middle of the calibrations.
	 */
	return state && rfkill_safe_init_done;
}