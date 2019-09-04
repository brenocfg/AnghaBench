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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tx_buffer; } ;
struct atl1e_adapter {TYPE_1__ tx_ring; int /*<<< orphan*/ * ring_vir_addr; int /*<<< orphan*/  ring_dma; int /*<<< orphan*/  ring_size; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atl1e_clean_rx_ring (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  atl1e_clean_tx_ring (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atl1e_free_ring_resources(struct atl1e_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;

	atl1e_clean_tx_ring(adapter);
	atl1e_clean_rx_ring(adapter);

	if (adapter->ring_vir_addr) {
		pci_free_consistent(pdev, adapter->ring_size,
				adapter->ring_vir_addr, adapter->ring_dma);
		adapter->ring_vir_addr = NULL;
	}

	if (adapter->tx_ring.tx_buffer) {
		kfree(adapter->tx_ring.tx_buffer);
		adapter->tx_ring.tx_buffer = NULL;
	}
}