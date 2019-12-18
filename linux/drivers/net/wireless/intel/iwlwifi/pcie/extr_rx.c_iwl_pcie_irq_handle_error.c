#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct iwl_trans_pcie {int /*<<< orphan*/  wait_command_queue; TYPE_4__** txq; } ;
struct iwl_trans {int /*<<< orphan*/  status; TYPE_3__* trans_cfg; int /*<<< orphan*/  op_mode; TYPE_1__* cfg; } ;
struct TYPE_8__ {int /*<<< orphan*/  stuck_timer; } ;
struct TYPE_7__ {TYPE_2__* base_params; } ;
struct TYPE_6__ {int num_of_queues; } ;
struct TYPE_5__ {int /*<<< orphan*/  apmg_not_supported; scalar_t__ internal_wimax_coex; } ;

/* Variables and functions */
 int /*<<< orphan*/  APMG_CLK_CTRL_REG ; 
 int /*<<< orphan*/  APMG_PS_CTRL_REG ; 
 int APMG_PS_CTRL_VAL_RESET_REQ ; 
 int APMS_CLK_VAL_MRB_FUNC_MODE ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  STATUS_SYNC_HCMD_ACTIVE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_op_mode_wimax_active (int /*<<< orphan*/ ) ; 
 int iwl_read_prph (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_fw_error (struct iwl_trans*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_pcie_irq_handle_error(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	int i;

	/* W/A for WiFi/WiMAX coex and WiMAX own the RF */
	if (trans->cfg->internal_wimax_coex &&
	    !trans->cfg->apmg_not_supported &&
	    (!(iwl_read_prph(trans, APMG_CLK_CTRL_REG) &
			     APMS_CLK_VAL_MRB_FUNC_MODE) ||
	     (iwl_read_prph(trans, APMG_PS_CTRL_REG) &
			    APMG_PS_CTRL_VAL_RESET_REQ))) {
		clear_bit(STATUS_SYNC_HCMD_ACTIVE, &trans->status);
		iwl_op_mode_wimax_active(trans->op_mode);
		wake_up(&trans_pcie->wait_command_queue);
		return;
	}

	for (i = 0; i < trans->trans_cfg->base_params->num_of_queues; i++) {
		if (!trans_pcie->txq[i])
			continue;
		del_timer(&trans_pcie->txq[i]->stuck_timer);
	}

	/* The STATUS_FW_ERROR bit is set in this function. This must happen
	 * before we wake up the command caller, to ensure a proper cleanup. */
	iwl_trans_fw_error(trans);

	clear_bit(STATUS_SYNC_HCMD_ACTIVE, &trans->status);
	wake_up(&trans_pcie->wait_command_queue);
}