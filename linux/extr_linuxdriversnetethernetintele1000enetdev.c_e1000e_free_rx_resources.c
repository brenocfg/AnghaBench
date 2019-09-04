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
struct e1000_ring {int count; int /*<<< orphan*/ * desc; int /*<<< orphan*/  dma; int /*<<< orphan*/  size; TYPE_1__* buffer_info; struct e1000_adapter* adapter; } ;
struct e1000_adapter {struct pci_dev* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  ps_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_clean_rx_ring (struct e1000_ring*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (TYPE_1__*) ; 

void e1000e_free_rx_resources(struct e1000_ring *rx_ring)
{
	struct e1000_adapter *adapter = rx_ring->adapter;
	struct pci_dev *pdev = adapter->pdev;
	int i;

	e1000_clean_rx_ring(rx_ring);

	for (i = 0; i < rx_ring->count; i++)
		kfree(rx_ring->buffer_info[i].ps_pages);

	vfree(rx_ring->buffer_info);
	rx_ring->buffer_info = NULL;

	dma_free_coherent(&pdev->dev, rx_ring->size, rx_ring->desc,
			  rx_ring->dma);
	rx_ring->desc = NULL;
}