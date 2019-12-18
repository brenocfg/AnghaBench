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
typedef  int u32 ;
struct iwl_trans_pcie {int ict_tbl_dma; int use_ict; int inta_mask; int /*<<< orphan*/  irq_lock; scalar_t__ ict_index; int /*<<< orphan*/  ict_tbl; } ;
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int CSR_DRAM_INIT_TBL_WRAP_CHECK ; 
 int CSR_DRAM_INIT_TBL_WRITE_POINTER ; 
 int CSR_DRAM_INT_TBL_ENABLE ; 
 int /*<<< orphan*/  CSR_DRAM_INT_TBL_REG ; 
 int /*<<< orphan*/  CSR_INT ; 
 int ICT_SHIFT ; 
 int /*<<< orphan*/  ICT_SIZE ; 
 int /*<<< orphan*/  IWL_DEBUG_ISR (struct iwl_trans*,char*,int) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  _iwl_disable_interrupts (struct iwl_trans*) ; 
 int /*<<< orphan*/  _iwl_enable_interrupts (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void iwl_pcie_reset_ict(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	u32 val;

	if (!trans_pcie->ict_tbl)
		return;

	spin_lock(&trans_pcie->irq_lock);
	_iwl_disable_interrupts(trans);

	memset(trans_pcie->ict_tbl, 0, ICT_SIZE);

	val = trans_pcie->ict_tbl_dma >> ICT_SHIFT;

	val |= CSR_DRAM_INT_TBL_ENABLE |
	       CSR_DRAM_INIT_TBL_WRAP_CHECK |
	       CSR_DRAM_INIT_TBL_WRITE_POINTER;

	IWL_DEBUG_ISR(trans, "CSR_DRAM_INT_TBL_REG =0x%x\n", val);

	iwl_write32(trans, CSR_DRAM_INT_TBL_REG, val);
	trans_pcie->use_ict = true;
	trans_pcie->ict_index = 0;
	iwl_write32(trans, CSR_INT, trans_pcie->inta_mask);
	_iwl_enable_interrupts(trans);
	spin_unlock(&trans_pcie->irq_lock);
}