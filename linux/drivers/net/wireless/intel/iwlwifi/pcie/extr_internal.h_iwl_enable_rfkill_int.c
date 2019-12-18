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
struct iwl_trans_pcie {int /*<<< orphan*/  fh_init_mask; int /*<<< orphan*/  inta_mask; int /*<<< orphan*/  msix_enabled; } ;
struct iwl_trans {TYPE_1__* trans_cfg; } ;
struct TYPE_2__ {scalar_t__ device_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int /*<<< orphan*/  CSR_GP_CNTRL_REG_FLAG_RFKILL_WAKE_L1A_EN ; 
 int /*<<< orphan*/  CSR_INT_BIT_RF_KILL ; 
 int /*<<< orphan*/  CSR_INT_MASK ; 
 int /*<<< orphan*/  CSR_MSIX_FH_INT_MASK_AD ; 
 int /*<<< orphan*/  IWL_DEBUG_ISR (struct iwl_trans*,char*) ; 
 scalar_t__ IWL_DEVICE_FAMILY_9000 ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  MSIX_HW_INT_CAUSES_REG_RF_KILL ; 
 int /*<<< orphan*/  iwl_enable_hw_int_msk_msix (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void iwl_enable_rfkill_int(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	IWL_DEBUG_ISR(trans, "Enabling rfkill interrupt\n");
	if (!trans_pcie->msix_enabled) {
		trans_pcie->inta_mask = CSR_INT_BIT_RF_KILL;
		iwl_write32(trans, CSR_INT_MASK, trans_pcie->inta_mask);
	} else {
		iwl_write32(trans, CSR_MSIX_FH_INT_MASK_AD,
			    trans_pcie->fh_init_mask);
		iwl_enable_hw_int_msk_msix(trans,
					   MSIX_HW_INT_CAUSES_REG_RF_KILL);
	}

	if (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_9000) {
		/*
		 * On 9000-series devices this bit isn't enabled by default, so
		 * when we power down the device we need set the bit to allow it
		 * to wake up the PCI-E bus for RF-kill interrupts.
		 */
		iwl_set_bit(trans, CSR_GP_CNTRL,
			    CSR_GP_CNTRL_REG_FLAG_RFKILL_WAKE_L1A_EN);
	}
}