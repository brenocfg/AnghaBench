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
struct msix_entry {int /*<<< orphan*/  entry; } ;
struct iwl_trans_pcie {struct iwl_trans* trans; } ;
struct iwl_trans {int /*<<< orphan*/  sync_cmd_lockdep_map; int /*<<< orphan*/  num_rx_queues; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  iwl_pcie_clear_irq (struct iwl_trans*,struct msix_entry*) ; 
 struct iwl_trans_pcie* iwl_pcie_get_trans_pcie (struct msix_entry*) ; 
 int /*<<< orphan*/  iwl_pcie_rx_handle (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  lock_map_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_map_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_iwlwifi_dev_irq_msix (int /*<<< orphan*/ ,struct msix_entry*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

irqreturn_t iwl_pcie_irq_rx_msix_handler(int irq, void *dev_id)
{
	struct msix_entry *entry = dev_id;
	struct iwl_trans_pcie *trans_pcie = iwl_pcie_get_trans_pcie(entry);
	struct iwl_trans *trans = trans_pcie->trans;

	trace_iwlwifi_dev_irq_msix(trans->dev, entry, false, 0, 0);

	if (WARN_ON(entry->entry >= trans->num_rx_queues))
		return IRQ_NONE;

	lock_map_acquire(&trans->sync_cmd_lockdep_map);

	local_bh_disable();
	iwl_pcie_rx_handle(trans, entry->entry);
	local_bh_enable();

	iwl_pcie_clear_irq(trans, entry);

	lock_map_release(&trans->sync_cmd_lockdep_map);

	return IRQ_HANDLED;
}