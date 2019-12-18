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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_trans_pcie {int /*<<< orphan*/  mutex; int /*<<< orphan*/  queue_used; int /*<<< orphan*/  queue_stopped; } ;
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_enable_interrupts (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_check_hw_rf_kill (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_ctxt_info_free (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_reset_ict (struct iwl_trans*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void iwl_trans_pcie_gen2_fw_alive(struct iwl_trans *trans, u32 scd_addr)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	iwl_pcie_reset_ict(trans);

	/* make sure all queue are not stopped/used */
	memset(trans_pcie->queue_stopped, 0, sizeof(trans_pcie->queue_stopped));
	memset(trans_pcie->queue_used, 0, sizeof(trans_pcie->queue_used));

	/* now that we got alive we can free the fw image & the context info.
	 * paging memory cannot be freed included since FW will still use it
	 */
	iwl_pcie_ctxt_info_free(trans);

	/*
	 * Re-enable all the interrupts, including the RF-Kill one, now that
	 * the firmware is alive.
	 */
	iwl_enable_interrupts(trans);
	mutex_lock(&trans_pcie->mutex);
	iwl_pcie_check_hw_rf_kill(trans);
	mutex_unlock(&trans_pcie->mutex);
}