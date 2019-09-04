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
struct lan743x_tx_descriptor {int dummy; } ;
struct lan743x_tx_buffer_info {int dummy; } ;
struct lan743x_tx {int ring_size; size_t ring_allocation_size; int head_dma_ptr; void* head_cpu_ptr; TYPE_1__* adapter; struct lan743x_tx_buffer_info* buffer_info; void* ring_dma_ptr; struct lan743x_tx_descriptor* ring_cpu_ptr; } ;
typedef  void* dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 size_t ALIGN (int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LAN743X_TX_RING_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int TX_CFG_B_TX_RING_LEN_MASK_ ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan743x_tx_ring_cleanup (struct lan743x_tx*) ; 
 void* pci_zalloc_consistent (int /*<<< orphan*/ ,int,void**) ; 

__attribute__((used)) static int lan743x_tx_ring_init(struct lan743x_tx *tx)
{
	size_t ring_allocation_size = 0;
	void *cpu_ptr = NULL;
	dma_addr_t dma_ptr;
	int ret = -ENOMEM;

	tx->ring_size = LAN743X_TX_RING_SIZE;
	if (tx->ring_size & ~TX_CFG_B_TX_RING_LEN_MASK_) {
		ret = -EINVAL;
		goto cleanup;
	}
	ring_allocation_size = ALIGN(tx->ring_size *
				     sizeof(struct lan743x_tx_descriptor),
				     PAGE_SIZE);
	dma_ptr = 0;
	cpu_ptr = pci_zalloc_consistent(tx->adapter->pdev,
					ring_allocation_size, &dma_ptr);
	if (!cpu_ptr) {
		ret = -ENOMEM;
		goto cleanup;
	}

	tx->ring_allocation_size = ring_allocation_size;
	tx->ring_cpu_ptr = (struct lan743x_tx_descriptor *)cpu_ptr;
	tx->ring_dma_ptr = dma_ptr;

	cpu_ptr = kcalloc(tx->ring_size, sizeof(*tx->buffer_info), GFP_KERNEL);
	if (!cpu_ptr) {
		ret = -ENOMEM;
		goto cleanup;
	}
	tx->buffer_info = (struct lan743x_tx_buffer_info *)cpu_ptr;
	dma_ptr = 0;
	cpu_ptr = pci_zalloc_consistent(tx->adapter->pdev,
					sizeof(*tx->head_cpu_ptr), &dma_ptr);
	if (!cpu_ptr) {
		ret = -ENOMEM;
		goto cleanup;
	}

	tx->head_cpu_ptr = cpu_ptr;
	tx->head_dma_ptr = dma_ptr;
	if (tx->head_dma_ptr & 0x3) {
		ret = -ENOMEM;
		goto cleanup;
	}

	return 0;

cleanup:
	lan743x_tx_ring_cleanup(tx);
	return ret;
}