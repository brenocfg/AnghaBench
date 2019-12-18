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
struct iwl_trans_pcie {int inta_mask; int /*<<< orphan*/  fh_init_mask; int /*<<< orphan*/  msix_enabled; } ;
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int CSR_INT_BIT_ALIVE ; 
 int CSR_INT_BIT_FH_RX ; 
 int /*<<< orphan*/  CSR_INT_MASK ; 
 int /*<<< orphan*/  IWL_DEBUG_ISR (struct iwl_trans*,char*) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  MSIX_HW_INT_CAUSES_REG_ALIVE ; 
 int /*<<< orphan*/  iwl_enable_fh_int_msk_msix (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_enable_hw_int_msk_msix (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void iwl_enable_fw_load_int_ctx_info(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	IWL_DEBUG_ISR(trans, "Enabling ALIVE interrupt only\n");

	if (!trans_pcie->msix_enabled) {
		/*
		 * When we'll receive the ALIVE interrupt, the ISR will call
		 * iwl_enable_fw_load_int_ctx_info again to set the ALIVE
		 * interrupt (which is not really needed anymore) but also the
		 * RX interrupt which will allow us to receive the ALIVE
		 * notification (which is Rx) and continue the flow.
		 */
		trans_pcie->inta_mask =  CSR_INT_BIT_ALIVE | CSR_INT_BIT_FH_RX;
		iwl_write32(trans, CSR_INT_MASK, trans_pcie->inta_mask);
	} else {
		iwl_enable_hw_int_msk_msix(trans,
					   MSIX_HW_INT_CAUSES_REG_ALIVE);
		/*
		 * Leave all the FH causes enabled to get the ALIVE
		 * notification.
		 */
		iwl_enable_fh_int_msk_msix(trans, trans_pcie->fh_init_mask);
	}
}