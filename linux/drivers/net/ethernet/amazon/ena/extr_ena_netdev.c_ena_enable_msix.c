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
struct ena_adapter {int msix_vecs; int /*<<< orphan*/  flags; int /*<<< orphan*/  netdev; scalar_t__ num_queues; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ ENA_ADMIN_MSIX_VEC ; 
 int /*<<< orphan*/  ENA_FLAG_MSIX_ENABLED ; 
 int ENA_MAX_MSIX_VEC (int) ; 
 int /*<<< orphan*/  ENA_MIN_MSIX_VEC ; 
 int ENOSPC ; 
 int EPERM ; 
 int /*<<< orphan*/  PCI_IRQ_MSIX ; 
 scalar_t__ ena_init_rx_cpu_rmap (struct ena_adapter*) ; 
 int /*<<< orphan*/  netif_dbg (struct ena_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_err (struct ena_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netif_notice (struct ena_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  netif_warn (struct ena_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int pci_alloc_irq_vectors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ena_enable_msix(struct ena_adapter *adapter, int num_queues)
{
	int msix_vecs, irq_cnt;

	if (test_bit(ENA_FLAG_MSIX_ENABLED, &adapter->flags)) {
		netif_err(adapter, probe, adapter->netdev,
			  "Error, MSI-X is already enabled\n");
		return -EPERM;
	}

	/* Reserved the max msix vectors we might need */
	msix_vecs = ENA_MAX_MSIX_VEC(num_queues);
	netif_dbg(adapter, probe, adapter->netdev,
		  "trying to enable MSI-X, vectors %d\n", msix_vecs);

	irq_cnt = pci_alloc_irq_vectors(adapter->pdev, ENA_MIN_MSIX_VEC,
					msix_vecs, PCI_IRQ_MSIX);

	if (irq_cnt < 0) {
		netif_err(adapter, probe, adapter->netdev,
			  "Failed to enable MSI-X. irq_cnt %d\n", irq_cnt);
		return -ENOSPC;
	}

	if (irq_cnt != msix_vecs) {
		netif_notice(adapter, probe, adapter->netdev,
			     "enable only %d MSI-X (out of %d), reduce the number of queues\n",
			     irq_cnt, msix_vecs);
		adapter->num_queues = irq_cnt - ENA_ADMIN_MSIX_VEC;
	}

	if (ena_init_rx_cpu_rmap(adapter))
		netif_warn(adapter, probe, adapter->netdev,
			   "Failed to map IRQs to CPUs\n");

	adapter->msix_vecs = irq_cnt;
	set_bit(ENA_FLAG_MSIX_ENABLED, &adapter->flags);

	return 0;
}