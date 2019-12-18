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
struct pch_gbe_rx_ring {unsigned int count; unsigned int rx_buff_pool_size; scalar_t__ rx_buff_pool; struct pch_gbe_buffer* buffer_info; int /*<<< orphan*/  rx_buff_pool_logic; } ;
struct pch_gbe_buffer {unsigned int length; scalar_t__ rx_buffer; } ;
struct pch_gbe_adapter {unsigned int rx_buffer_len; struct pci_dev* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PCH_GBE_RESERVE_MEMORY ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pch_gbe_alloc_rx_buffers_pool(struct pch_gbe_adapter *adapter,
			 struct pch_gbe_rx_ring *rx_ring, int cleaned_count)
{
	struct pci_dev *pdev = adapter->pdev;
	struct pch_gbe_buffer *buffer_info;
	unsigned int i;
	unsigned int bufsz;
	unsigned int size;

	bufsz = adapter->rx_buffer_len;

	size = rx_ring->count * bufsz + PCH_GBE_RESERVE_MEMORY;
	rx_ring->rx_buff_pool =
		dma_alloc_coherent(&pdev->dev, size,
				   &rx_ring->rx_buff_pool_logic, GFP_KERNEL);
	if (!rx_ring->rx_buff_pool)
		return -ENOMEM;

	rx_ring->rx_buff_pool_size = size;
	for (i = 0; i < rx_ring->count; i++) {
		buffer_info = &rx_ring->buffer_info[i];
		buffer_info->rx_buffer = rx_ring->rx_buff_pool + bufsz * i;
		buffer_info->length = bufsz;
	}
	return 0;
}