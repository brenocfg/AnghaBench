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
struct iwl_trans_pcie {int opmode_down; int is_down; int /*<<< orphan*/  mutex; } ;
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,int) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_enable_rfkill_int (struct iwl_trans*) ; 
 int iwl_pcie_apm_init (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_check_hw_rf_kill (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_init_msix (struct iwl_trans_pcie*) ; 
 int iwl_pcie_prepare_card_hw (struct iwl_trans*) ; 
 int iwl_trans_pcie_clear_persistence_bit (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_trans_pcie_sw_reset (struct iwl_trans*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _iwl_trans_pcie_start_hw(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	int err;

	lockdep_assert_held(&trans_pcie->mutex);

	err = iwl_pcie_prepare_card_hw(trans);
	if (err) {
		IWL_ERR(trans, "Error while preparing HW: %d\n", err);
		return err;
	}

	err = iwl_trans_pcie_clear_persistence_bit(trans);
	if (err)
		return err;

	iwl_trans_pcie_sw_reset(trans);

	err = iwl_pcie_apm_init(trans);
	if (err)
		return err;

	iwl_pcie_init_msix(trans_pcie);

	/* From now on, the op_mode will be kept updated about RF kill state */
	iwl_enable_rfkill_int(trans);

	trans_pcie->opmode_down = false;

	/* Set is_down to false here so that...*/
	trans_pcie->is_down = false;

	/* ...rfkill can call stop_device and set it false if needed */
	iwl_pcie_check_hw_rf_kill(trans);

	return 0;
}