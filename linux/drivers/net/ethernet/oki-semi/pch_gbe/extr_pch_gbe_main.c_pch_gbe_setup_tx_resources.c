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
struct pch_gbe_tx_ring {int count; int size; scalar_t__ next_to_use; scalar_t__ next_to_clean; scalar_t__ dma; int /*<<< orphan*/  desc; int /*<<< orphan*/  buffer_info; } ;
struct pch_gbe_tx_desc {int /*<<< orphan*/  gbec_status; } ;
struct pch_gbe_buffer {int dummy; } ;
struct pch_gbe_adapter {int /*<<< orphan*/  netdev; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSC_INIT16 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pch_gbe_tx_desc* PCH_GBE_TX_DESC (struct pch_gbe_tx_ring,int) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned long long,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vzalloc (int) ; 

int pch_gbe_setup_tx_resources(struct pch_gbe_adapter *adapter,
				struct pch_gbe_tx_ring *tx_ring)
{
	struct pci_dev *pdev = adapter->pdev;
	struct pch_gbe_tx_desc *tx_desc;
	int size;
	int desNo;

	size = (int)sizeof(struct pch_gbe_buffer) * tx_ring->count;
	tx_ring->buffer_info = vzalloc(size);
	if (!tx_ring->buffer_info)
		return -ENOMEM;

	tx_ring->size = tx_ring->count * (int)sizeof(struct pch_gbe_tx_desc);

	tx_ring->desc = dma_alloc_coherent(&pdev->dev, tx_ring->size,
					   &tx_ring->dma, GFP_KERNEL);
	if (!tx_ring->desc) {
		vfree(tx_ring->buffer_info);
		return -ENOMEM;
	}

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

	for (desNo = 0; desNo < tx_ring->count; desNo++) {
		tx_desc = PCH_GBE_TX_DESC(*tx_ring, desNo);
		tx_desc->gbec_status = DSC_INIT16;
	}
	netdev_dbg(adapter->netdev,
		   "tx_ring->desc = 0x%p  tx_ring->dma = 0x%08llx next_to_clean = 0x%08x  next_to_use = 0x%08x\n",
		   tx_ring->desc, (unsigned long long)tx_ring->dma,
		   tx_ring->next_to_clean, tx_ring->next_to_use);
	return 0;
}