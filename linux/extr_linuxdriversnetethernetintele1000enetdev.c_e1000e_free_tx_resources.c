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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct e1000_ring {int /*<<< orphan*/ * desc; int /*<<< orphan*/  dma; int /*<<< orphan*/  size; int /*<<< orphan*/ * buffer_info; struct e1000_adapter* adapter; } ;
struct e1000_adapter {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_clean_tx_ring (struct e1000_ring*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void e1000e_free_tx_resources(struct e1000_ring *tx_ring)
{
	struct e1000_adapter *adapter = tx_ring->adapter;
	struct pci_dev *pdev = adapter->pdev;

	e1000_clean_tx_ring(tx_ring);

	vfree(tx_ring->buffer_info);
	tx_ring->buffer_info = NULL;

	dma_free_coherent(&pdev->dev, tx_ring->size, tx_ring->desc,
			  tx_ring->dma);
	tx_ring->desc = NULL;
}