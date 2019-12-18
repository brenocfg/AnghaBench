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
struct timer_list {int dummy; } ;
struct iwl_txq {scalar_t__ read_ptr; scalar_t__ write_ptr; int /*<<< orphan*/  lock; struct iwl_trans_pcie* trans_pcie; } ;
struct iwl_trans_pcie {int dummy; } ;
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 struct iwl_txq* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_force_nmi (struct iwl_trans*) ; 
 struct iwl_trans* iwl_trans_pcie_get_trans (struct iwl_trans_pcie*) ; 
 int /*<<< orphan*/  iwl_trans_pcie_log_scd_error (struct iwl_trans*,struct iwl_txq*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stuck_timer ; 
 struct iwl_txq* txq ; 

__attribute__((used)) static void iwl_pcie_txq_stuck_timer(struct timer_list *t)
{
	struct iwl_txq *txq = from_timer(txq, t, stuck_timer);
	struct iwl_trans_pcie *trans_pcie = txq->trans_pcie;
	struct iwl_trans *trans = iwl_trans_pcie_get_trans(trans_pcie);

	spin_lock(&txq->lock);
	/* check if triggered erroneously */
	if (txq->read_ptr == txq->write_ptr) {
		spin_unlock(&txq->lock);
		return;
	}
	spin_unlock(&txq->lock);

	iwl_trans_pcie_log_scd_error(trans, txq);

	iwl_force_nmi(trans);
}