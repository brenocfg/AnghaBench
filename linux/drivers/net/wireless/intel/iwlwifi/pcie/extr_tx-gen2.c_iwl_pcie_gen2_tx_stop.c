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
struct iwl_trans_pcie {int /*<<< orphan*/ * txq; int /*<<< orphan*/  queue_used; int /*<<< orphan*/  queue_stopped; } ;
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_gen2_txq_unmap (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void iwl_pcie_gen2_tx_stop(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	int txq_id;

	/*
	 * This function can be called before the op_mode disabled the
	 * queues. This happens when we have an rfkill interrupt.
	 * Since we stop Tx altogether - mark the queues as stopped.
	 */
	memset(trans_pcie->queue_stopped, 0, sizeof(trans_pcie->queue_stopped));
	memset(trans_pcie->queue_used, 0, sizeof(trans_pcie->queue_used));

	/* Unmap DMA from host system and free skb's */
	for (txq_id = 0; txq_id < ARRAY_SIZE(trans_pcie->txq); txq_id++) {
		if (!trans_pcie->txq[txq_id])
			continue;
		iwl_pcie_gen2_txq_unmap(trans, txq_id);
	}
}