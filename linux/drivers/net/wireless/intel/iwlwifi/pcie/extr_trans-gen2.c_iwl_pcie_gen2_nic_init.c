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
struct iwl_trans_pcie {int /*<<< orphan*/  cmd_queue; int /*<<< orphan*/  irq_lock; } ;
struct iwl_trans {int /*<<< orphan*/  op_mode; TYPE_1__* cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  min_txq_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_MAC_SHADOW_REG_CTRL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IWL_CMD_QUEUE_SIZE ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_trans*,char*) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_op_mode_nic_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_pcie_gen2_apm_init (struct iwl_trans*) ; 
 scalar_t__ iwl_pcie_gen2_rx_init (struct iwl_trans*) ; 
 scalar_t__ iwl_pcie_gen2_tx_init (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int max_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static int iwl_pcie_gen2_nic_init(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	int queue_size = max_t(u32, IWL_CMD_QUEUE_SIZE,
			       trans->cfg->min_txq_size);

	/* TODO: most of the logic can be removed in A0 - but not in Z0 */
	spin_lock(&trans_pcie->irq_lock);
	iwl_pcie_gen2_apm_init(trans);
	spin_unlock(&trans_pcie->irq_lock);

	iwl_op_mode_nic_config(trans->op_mode);

	/* Allocate the RX queue, or reset if it is already allocated */
	if (iwl_pcie_gen2_rx_init(trans))
		return -ENOMEM;

	/* Allocate or reset and init all Tx and Command queues */
	if (iwl_pcie_gen2_tx_init(trans, trans_pcie->cmd_queue, queue_size))
		return -ENOMEM;

	/* enable shadow regs in HW */
	iwl_set_bit(trans, CSR_MAC_SHADOW_REG_CTRL, 0x800FFFFF);
	IWL_DEBUG_INFO(trans, "Enabling shadow registers in device\n");

	return 0;
}