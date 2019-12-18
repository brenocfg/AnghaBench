#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iwl_trans_pcie {int cmd_hold_nic_awake; int /*<<< orphan*/  reg_lock; } ;
struct iwl_trans {TYPE_2__* trans_cfg; } ;
struct TYPE_6__ {int /*<<< orphan*/  flag_mac_access_req; } ;
struct TYPE_5__ {TYPE_3__* csr; TYPE_1__* base_params; } ;
struct TYPE_4__ {int /*<<< orphan*/  apmg_wake_up_wa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __iwl_trans_pcie_clear_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_pcie_clear_cmd_in_flight(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	lockdep_assert_held(&trans_pcie->reg_lock);

	if (!trans->trans_cfg->base_params->apmg_wake_up_wa)
		return;
	if (WARN_ON(!trans_pcie->cmd_hold_nic_awake))
		return;

	trans_pcie->cmd_hold_nic_awake = false;
	__iwl_trans_pcie_clear_bit(trans, CSR_GP_CNTRL,
				   BIT(trans->trans_cfg->csr->flag_mac_access_req));
}