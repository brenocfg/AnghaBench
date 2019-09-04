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
typedef  union e1000_adv_rx_desc {int dummy; } e1000_adv_rx_desc ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct igbvf_ring {int count; int size; int /*<<< orphan*/ * buffer_info; struct igbvf_adapter* adapter; scalar_t__ next_to_use; scalar_t__ next_to_clean; int /*<<< orphan*/  desc; int /*<<< orphan*/  dma; } ;
struct igbvf_buffer {int dummy; } ;
struct igbvf_adapter {struct pci_dev* pdev; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vzalloc (int) ; 

int igbvf_setup_rx_resources(struct igbvf_adapter *adapter,
			     struct igbvf_ring *rx_ring)
{
	struct pci_dev *pdev = adapter->pdev;
	int size, desc_len;

	size = sizeof(struct igbvf_buffer) * rx_ring->count;
	rx_ring->buffer_info = vzalloc(size);
	if (!rx_ring->buffer_info)
		goto err;

	desc_len = sizeof(union e1000_adv_rx_desc);

	/* Round up to nearest 4K */
	rx_ring->size = rx_ring->count * desc_len;
	rx_ring->size = ALIGN(rx_ring->size, 4096);

	rx_ring->desc = dma_alloc_coherent(&pdev->dev, rx_ring->size,
					   &rx_ring->dma, GFP_KERNEL);
	if (!rx_ring->desc)
		goto err;

	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;

	rx_ring->adapter = adapter;

	return 0;

err:
	vfree(rx_ring->buffer_info);
	rx_ring->buffer_info = NULL;
	dev_err(&adapter->pdev->dev,
		"Unable to allocate memory for the receive descriptor ring\n");
	return -ENOMEM;
}