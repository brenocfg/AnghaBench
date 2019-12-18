#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iwl_txq {int write_ptr; int /*<<< orphan*/  lock; int /*<<< orphan*/  block; } ;
struct iwl_trans_pcie {int cmd_queue; struct iwl_txq** txq; } ;
struct iwl_trans {TYPE_2__* trans_cfg; } ;
struct TYPE_4__ {TYPE_1__* base_params; } ;
struct TYPE_3__ {int num_of_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  HBUS_TARG_WRPTR ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_trans_pcie_block_txq_ptrs(struct iwl_trans *trans, bool block)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	int i;

	for (i = 0; i < trans->trans_cfg->base_params->num_of_queues; i++) {
		struct iwl_txq *txq = trans_pcie->txq[i];

		if (i == trans_pcie->cmd_queue)
			continue;

		spin_lock_bh(&txq->lock);

		if (!block && !(WARN_ON_ONCE(!txq->block))) {
			txq->block--;
			if (!txq->block) {
				iwl_write32(trans, HBUS_TARG_WRPTR,
					    txq->write_ptr | (i << 8));
			}
		} else if (block) {
			txq->block++;
		}

		spin_unlock_bh(&txq->lock);
	}
}