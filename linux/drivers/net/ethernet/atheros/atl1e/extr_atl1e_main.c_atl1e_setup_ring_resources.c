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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct atl1e_tx_ring {int dma; int count; int cmb_dma; int /*<<< orphan*/  cmb; int /*<<< orphan*/ * tx_buffer; int /*<<< orphan*/  desc; } ;
struct atl1e_tx_buffer {int dummy; } ;
struct atl1e_tpd_desc {int dummy; } ;
struct atl1e_rx_ring {scalar_t__ real_page_size; struct atl1e_rx_page_desc* rx_page_desc; } ;
struct atl1e_rx_page_desc {TYPE_1__* rx_page; } ;
struct atl1e_adapter {int ring_size; int ring_dma; int num_rx_queues; int /*<<< orphan*/ * ring_vir_addr; int /*<<< orphan*/  netdev; struct atl1e_rx_ring rx_ring; struct atl1e_tx_ring tx_ring; struct pci_dev* pdev; } ;
struct TYPE_2__ {int dma; int write_offset_dma; int /*<<< orphan*/  write_offset_addr; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int AT_PAGE_NUM_PER_QUEUE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pci_zalloc_consistent (struct pci_dev*,int,int*) ; 
 void* roundup (int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int atl1e_setup_ring_resources(struct atl1e_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;
	struct atl1e_tx_ring *tx_ring;
	struct atl1e_rx_ring *rx_ring;
	struct atl1e_rx_page_desc  *rx_page_desc;
	int size, i, j;
	u32 offset = 0;
	int err = 0;

	if (adapter->ring_vir_addr != NULL)
		return 0; /* alloced already */

	tx_ring = &adapter->tx_ring;
	rx_ring = &adapter->rx_ring;

	/* real ring DMA buffer */

	size = adapter->ring_size;
	adapter->ring_vir_addr = pci_zalloc_consistent(pdev, adapter->ring_size,
						       &adapter->ring_dma);
	if (adapter->ring_vir_addr == NULL) {
		netdev_err(adapter->netdev,
			   "pci_alloc_consistent failed, size = D%d\n", size);
		return -ENOMEM;
	}

	rx_page_desc = rx_ring->rx_page_desc;

	/* Init TPD Ring */
	tx_ring->dma = roundup(adapter->ring_dma, 8);
	offset = tx_ring->dma - adapter->ring_dma;
	tx_ring->desc = adapter->ring_vir_addr + offset;
	size = sizeof(struct atl1e_tx_buffer) * (tx_ring->count);
	tx_ring->tx_buffer = kzalloc(size, GFP_KERNEL);
	if (tx_ring->tx_buffer == NULL) {
		err = -ENOMEM;
		goto failed;
	}

	/* Init RXF-Pages */
	offset += (sizeof(struct atl1e_tpd_desc) * tx_ring->count);
	offset = roundup(offset, 32);

	for (i = 0; i < adapter->num_rx_queues; i++) {
		for (j = 0; j < AT_PAGE_NUM_PER_QUEUE; j++) {
			rx_page_desc[i].rx_page[j].dma =
				adapter->ring_dma + offset;
			rx_page_desc[i].rx_page[j].addr =
				adapter->ring_vir_addr + offset;
			offset += rx_ring->real_page_size;
		}
	}

	/* Init CMB dma address */
	tx_ring->cmb_dma = adapter->ring_dma + offset;
	tx_ring->cmb = adapter->ring_vir_addr + offset;
	offset += sizeof(u32);

	for (i = 0; i < adapter->num_rx_queues; i++) {
		for (j = 0; j < AT_PAGE_NUM_PER_QUEUE; j++) {
			rx_page_desc[i].rx_page[j].write_offset_dma =
				adapter->ring_dma + offset;
			rx_page_desc[i].rx_page[j].write_offset_addr =
				adapter->ring_vir_addr + offset;
			offset += sizeof(u32);
		}
	}

	if (unlikely(offset > adapter->ring_size)) {
		netdev_err(adapter->netdev, "offset(%d) > ring size(%d) !!\n",
			   offset, adapter->ring_size);
		err = -1;
		goto failed;
	}

	return 0;
failed:
	if (adapter->ring_vir_addr != NULL) {
		pci_free_consistent(pdev, adapter->ring_size,
				adapter->ring_vir_addr, adapter->ring_dma);
		adapter->ring_vir_addr = NULL;
	}
	return err;
}