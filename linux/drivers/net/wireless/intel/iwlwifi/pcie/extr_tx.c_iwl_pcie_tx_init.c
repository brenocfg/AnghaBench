#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int dma; } ;
struct iwl_trans_pcie {int cmd_queue; TYPE_5__** txq; int /*<<< orphan*/  irq_lock; TYPE_1__ kw; int /*<<< orphan*/  txq_memory; } ;
struct iwl_trans {TYPE_4__* trans_cfg; TYPE_2__* cfg; } ;
struct TYPE_10__ {int dma_addr; } ;
struct TYPE_9__ {TYPE_3__* base_params; } ;
struct TYPE_8__ {int num_of_queues; } ;
struct TYPE_7__ {int /*<<< orphan*/  min_256_ba_txq_size; int /*<<< orphan*/  min_txq_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FH_KW_MEM_ADDR_REG ; 
 int /*<<< orphan*/  FH_MEM_CBBC_QUEUE (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  IWL_CMD_QUEUE_SIZE ; 
 int /*<<< orphan*/  IWL_DEFAULT_QUEUE_SIZE ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,int) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  SCD_GP_CTRL ; 
 int /*<<< orphan*/  SCD_GP_CTRL_AUTO_ACTIVE_MODE ; 
 int /*<<< orphan*/  SCD_GP_CTRL_ENABLE_31_QUEUES ; 
 int iwl_pcie_tx_alloc (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_tx_free (struct iwl_trans*) ; 
 int iwl_pcie_txq_init (struct iwl_trans*,TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  iwl_scd_deactivate_fifos (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_set_bits_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write_direct32 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int max_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u32 ; 

int iwl_pcie_tx_init(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	int ret;
	int txq_id, slots_num;
	bool alloc = false;

	if (!trans_pcie->txq_memory) {
		ret = iwl_pcie_tx_alloc(trans);
		if (ret)
			goto error;
		alloc = true;
	}

	spin_lock(&trans_pcie->irq_lock);

	/* Turn off all Tx DMA fifos */
	iwl_scd_deactivate_fifos(trans);

	/* Tell NIC where to find the "keep warm" buffer */
	iwl_write_direct32(trans, FH_KW_MEM_ADDR_REG,
			   trans_pcie->kw.dma >> 4);

	spin_unlock(&trans_pcie->irq_lock);

	/* Alloc and init all Tx queues, including the command queue (#4/#9) */
	for (txq_id = 0; txq_id < trans->trans_cfg->base_params->num_of_queues;
	     txq_id++) {
		bool cmd_queue = (txq_id == trans_pcie->cmd_queue);

		if (cmd_queue)
			slots_num = max_t(u32, IWL_CMD_QUEUE_SIZE,
					  trans->cfg->min_txq_size);
		else
			slots_num = max_t(u32, IWL_DEFAULT_QUEUE_SIZE,
					  trans->cfg->min_256_ba_txq_size);
		ret = iwl_pcie_txq_init(trans, trans_pcie->txq[txq_id],
					slots_num, cmd_queue);
		if (ret) {
			IWL_ERR(trans, "Tx %d queue init failed\n", txq_id);
			goto error;
		}

		/*
		 * Tell nic where to find circular buffer of TFDs for a
		 * given Tx queue, and enable the DMA channel used for that
		 * queue.
		 * Circular buffer (TFD queue in DRAM) physical base address
		 */
		iwl_write_direct32(trans, FH_MEM_CBBC_QUEUE(trans, txq_id),
				   trans_pcie->txq[txq_id]->dma_addr >> 8);
	}

	iwl_set_bits_prph(trans, SCD_GP_CTRL, SCD_GP_CTRL_AUTO_ACTIVE_MODE);
	if (trans->trans_cfg->base_params->num_of_queues > 20)
		iwl_set_bits_prph(trans, SCD_GP_CTRL,
				  SCD_GP_CTRL_ENABLE_31_QUEUES);

	return 0;
error:
	/*Upon error, free only if we allocated something */
	if (alloc)
		iwl_pcie_tx_free(trans);
	return ret;
}