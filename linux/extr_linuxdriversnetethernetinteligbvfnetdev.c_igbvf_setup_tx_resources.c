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
typedef  union e1000_adv_tx_desc {int dummy; } e1000_adv_tx_desc ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct igbvf_ring {int count; int size; int /*<<< orphan*/  buffer_info; scalar_t__ next_to_clean; scalar_t__ next_to_use; struct igbvf_adapter* adapter; int /*<<< orphan*/  desc; int /*<<< orphan*/  dma; } ;
struct igbvf_buffer {int dummy; } ;
struct igbvf_adapter {struct pci_dev* pdev; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vzalloc (int) ; 

int igbvf_setup_tx_resources(struct igbvf_adapter *adapter,
			     struct igbvf_ring *tx_ring)
{
	struct pci_dev *pdev = adapter->pdev;
	int size;

	size = sizeof(struct igbvf_buffer) * tx_ring->count;
	tx_ring->buffer_info = vzalloc(size);
	if (!tx_ring->buffer_info)
		goto err;

	/* round up to nearest 4K */
	tx_ring->size = tx_ring->count * sizeof(union e1000_adv_tx_desc);
	tx_ring->size = ALIGN(tx_ring->size, 4096);

	tx_ring->desc = dma_alloc_coherent(&pdev->dev, tx_ring->size,
					   &tx_ring->dma, GFP_KERNEL);
	if (!tx_ring->desc)
		goto err;

	tx_ring->adapter = adapter;
	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

	return 0;
err:
	vfree(tx_ring->buffer_info);
	dev_err(&adapter->pdev->dev,
		"Unable to allocate memory for the transmit descriptor ring\n");
	return -ENOMEM;
}