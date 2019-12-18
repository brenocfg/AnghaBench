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
struct ixgb_rx_desc {int dummy; } ;
struct ixgb_desc_ring {int count; int size; scalar_t__ next_to_use; scalar_t__ next_to_clean; int /*<<< orphan*/  buffer_info; int /*<<< orphan*/  desc; int /*<<< orphan*/  dma; } ;
struct ixgb_buffer {int dummy; } ;
struct ixgb_adapter {struct pci_dev* pdev; struct ixgb_desc_ring rx_ring; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vzalloc (int) ; 

int
ixgb_setup_rx_resources(struct ixgb_adapter *adapter)
{
	struct ixgb_desc_ring *rxdr = &adapter->rx_ring;
	struct pci_dev *pdev = adapter->pdev;
	int size;

	size = sizeof(struct ixgb_buffer) * rxdr->count;
	rxdr->buffer_info = vzalloc(size);
	if (!rxdr->buffer_info)
		return -ENOMEM;

	/* Round up to nearest 4K */

	rxdr->size = rxdr->count * sizeof(struct ixgb_rx_desc);
	rxdr->size = ALIGN(rxdr->size, 4096);

	rxdr->desc = dma_alloc_coherent(&pdev->dev, rxdr->size, &rxdr->dma,
					GFP_KERNEL);

	if (!rxdr->desc) {
		vfree(rxdr->buffer_info);
		return -ENOMEM;
	}

	rxdr->next_to_clean = 0;
	rxdr->next_to_use = 0;

	return 0;
}