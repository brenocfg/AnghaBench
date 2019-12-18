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
struct iwl_trans {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_RFKILL_HW ; 
 int /*<<< orphan*/  STATUS_RFKILL_OPMODE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int iwl_is_rfkill_set (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_trans_pcie_rf_kill (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void iwl_trans_pcie_handle_stop_rfkill(struct iwl_trans *trans,
				       bool was_in_rfkill)
{
	bool hw_rfkill;

	/*
	 * Check again since the RF kill state may have changed while
	 * all the interrupts were disabled, in this case we couldn't
	 * receive the RF kill interrupt and update the state in the
	 * op_mode.
	 * Don't call the op_mode if the rkfill state hasn't changed.
	 * This allows the op_mode to call stop_device from the rfkill
	 * notification without endless recursion. Under very rare
	 * circumstances, we might have a small recursion if the rfkill
	 * state changed exactly now while we were called from stop_device.
	 * This is very unlikely but can happen and is supported.
	 */
	hw_rfkill = iwl_is_rfkill_set(trans);
	if (hw_rfkill) {
		set_bit(STATUS_RFKILL_HW, &trans->status);
		set_bit(STATUS_RFKILL_OPMODE, &trans->status);
	} else {
		clear_bit(STATUS_RFKILL_HW, &trans->status);
		clear_bit(STATUS_RFKILL_OPMODE, &trans->status);
	}
	if (hw_rfkill != was_in_rfkill)
		iwl_trans_pcie_rf_kill(trans, hw_rfkill);
}