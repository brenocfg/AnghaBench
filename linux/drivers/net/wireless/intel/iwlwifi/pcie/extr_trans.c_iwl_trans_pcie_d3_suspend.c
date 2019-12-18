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
struct iwl_trans_pcie {int sx_complete; int /*<<< orphan*/  sx_waitq; } ;
struct iwl_trans {TYPE_1__* trans_cfg; } ;
struct TYPE_2__ {scalar_t__ device_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG ; 
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG_PERSIST_MODE ; 
 int ETIMEDOUT ; 
 int HZ ; 
 scalar_t__ IWL_DEVICE_FAMILY_AX210 ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  UREG_DOORBELL_TO_ISR6 ; 
 int /*<<< orphan*/  UREG_DOORBELL_TO_ISR6_SUSPEND ; 
 int /*<<< orphan*/  iwl_pcie_d3_complete_suspend (struct iwl_trans*,int,int) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write_umac_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int iwl_trans_pcie_d3_suspend(struct iwl_trans *trans, bool test,
				     bool reset)
{
	int ret;
	struct iwl_trans_pcie *trans_pcie =  IWL_TRANS_GET_PCIE_TRANS(trans);

	/*
	 * Family IWL_DEVICE_FAMILY_AX210 and above persist mode is set by FW.
	 */
	if (!reset && trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_AX210) {
		/* Enable persistence mode to avoid reset */
		iwl_set_bit(trans, CSR_HW_IF_CONFIG_REG,
			    CSR_HW_IF_CONFIG_REG_PERSIST_MODE);
	}

	if (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210) {
		iwl_write_umac_prph(trans, UREG_DOORBELL_TO_ISR6,
				    UREG_DOORBELL_TO_ISR6_SUSPEND);

		ret = wait_event_timeout(trans_pcie->sx_waitq,
					 trans_pcie->sx_complete, 2 * HZ);
		/*
		 * Invalidate it toward resume.
		 */
		trans_pcie->sx_complete = false;

		if (!ret) {
			IWL_ERR(trans, "Timeout entering D3\n");
			return -ETIMEDOUT;
		}
	}
	iwl_pcie_d3_complete_suspend(trans, test, reset);

	return 0;
}