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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * desc; int /*<<< orphan*/  dma; int /*<<< orphan*/  size; int /*<<< orphan*/ * buffer_info; } ;
struct ixgb_adapter {TYPE_1__ tx_ring; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgb_clean_tx_ring (struct ixgb_adapter*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void
ixgb_free_tx_resources(struct ixgb_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;

	ixgb_clean_tx_ring(adapter);

	vfree(adapter->tx_ring.buffer_info);
	adapter->tx_ring.buffer_info = NULL;

	dma_free_coherent(&pdev->dev, adapter->tx_ring.size,
			  adapter->tx_ring.desc, adapter->tx_ring.dma);

	adapter->tx_ring.desc = NULL;
}