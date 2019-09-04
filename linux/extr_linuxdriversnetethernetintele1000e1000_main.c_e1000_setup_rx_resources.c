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
struct e1000_rx_ring {int count; int size; void* desc; int /*<<< orphan*/ * rx_skb_top; scalar_t__ next_to_use; scalar_t__ next_to_clean; int /*<<< orphan*/  dma; int /*<<< orphan*/  buffer_info; } ;
struct e1000_rx_desc {int dummy; } ;
struct e1000_rx_buffer {int dummy; } ;
struct e1000_adapter {struct pci_dev* pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_check_64k_bound (struct e1000_adapter*,void*,int) ; 
 int /*<<< orphan*/  e_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vzalloc (int) ; 

__attribute__((used)) static int e1000_setup_rx_resources(struct e1000_adapter *adapter,
				    struct e1000_rx_ring *rxdr)
{
	struct pci_dev *pdev = adapter->pdev;
	int size, desc_len;

	size = sizeof(struct e1000_rx_buffer) * rxdr->count;
	rxdr->buffer_info = vzalloc(size);
	if (!rxdr->buffer_info)
		return -ENOMEM;

	desc_len = sizeof(struct e1000_rx_desc);

	/* Round up to nearest 4K */

	rxdr->size = rxdr->count * desc_len;
	rxdr->size = ALIGN(rxdr->size, 4096);

	rxdr->desc = dma_alloc_coherent(&pdev->dev, rxdr->size, &rxdr->dma,
					GFP_KERNEL);
	if (!rxdr->desc) {
setup_rx_desc_die:
		vfree(rxdr->buffer_info);
		return -ENOMEM;
	}

	/* Fix for errata 23, can't cross 64kB boundary */
	if (!e1000_check_64k_bound(adapter, rxdr->desc, rxdr->size)) {
		void *olddesc = rxdr->desc;
		dma_addr_t olddma = rxdr->dma;
		e_err(rx_err, "rxdr align check failed: %u bytes at %p\n",
		      rxdr->size, rxdr->desc);
		/* Try again, without freeing the previous */
		rxdr->desc = dma_alloc_coherent(&pdev->dev, rxdr->size,
						&rxdr->dma, GFP_KERNEL);
		/* Failed allocation, critical failure */
		if (!rxdr->desc) {
			dma_free_coherent(&pdev->dev, rxdr->size, olddesc,
					  olddma);
			goto setup_rx_desc_die;
		}

		if (!e1000_check_64k_bound(adapter, rxdr->desc, rxdr->size)) {
			/* give up */
			dma_free_coherent(&pdev->dev, rxdr->size, rxdr->desc,
					  rxdr->dma);
			dma_free_coherent(&pdev->dev, rxdr->size, olddesc,
					  olddma);
			e_err(probe, "Unable to allocate aligned memory for "
			      "the Rx descriptor ring\n");
			goto setup_rx_desc_die;
		} else {
			/* Free old allocation, new allocation was successful */
			dma_free_coherent(&pdev->dev, rxdr->size, olddesc,
					  olddma);
		}
	}
	memset(rxdr->desc, 0, rxdr->size);

	rxdr->next_to_clean = 0;
	rxdr->next_to_use = 0;
	rxdr->rx_skb_top = NULL;

	return 0;
}