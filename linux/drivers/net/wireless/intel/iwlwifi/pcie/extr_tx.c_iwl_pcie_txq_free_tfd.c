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
struct sk_buff {int dummy; } ;
struct iwl_txq {int read_ptr; TYPE_1__* entries; int /*<<< orphan*/  lock; } ;
struct iwl_trans {int /*<<< orphan*/  op_mode; } ;
struct TYPE_2__ {struct sk_buff* skb; int /*<<< orphan*/  meta; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_op_mode_free_skb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int iwl_pcie_get_cmd_index (struct iwl_txq*,int) ; 
 int /*<<< orphan*/  iwl_pcie_tfd_unmap (struct iwl_trans*,int /*<<< orphan*/ *,struct iwl_txq*,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void iwl_pcie_txq_free_tfd(struct iwl_trans *trans, struct iwl_txq *txq)
{
	/* rd_ptr is bounded by TFD_QUEUE_SIZE_MAX and
	 * idx is bounded by n_window
	 */
	int rd_ptr = txq->read_ptr;
	int idx = iwl_pcie_get_cmd_index(txq, rd_ptr);

	lockdep_assert_held(&txq->lock);

	/* We have only q->n_window txq->entries, but we use
	 * TFD_QUEUE_SIZE_MAX tfds
	 */
	iwl_pcie_tfd_unmap(trans, &txq->entries[idx].meta, txq, rd_ptr);

	/* free SKB */
	if (txq->entries) {
		struct sk_buff *skb;

		skb = txq->entries[idx].skb;

		/* Can be called from irqs-disabled context
		 * If skb is not NULL, it means that the whole queue is being
		 * freed and that the queue is not empty - free the skb
		 */
		if (skb) {
			iwl_op_mode_free_skb(trans->op_mode, skb);
			txq->entries[idx].skb = NULL;
		}
	}
}