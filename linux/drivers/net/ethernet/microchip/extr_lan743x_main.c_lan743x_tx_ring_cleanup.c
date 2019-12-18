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
struct lan743x_tx {void* ring_cpu_ptr; int ring_allocation_size; scalar_t__ ring_size; scalar_t__ ring_dma_ptr; TYPE_1__* adapter; int /*<<< orphan*/ * buffer_info; scalar_t__ head_dma_ptr; int /*<<< orphan*/ * head_cpu_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,void*,scalar_t__) ; 

__attribute__((used)) static void lan743x_tx_ring_cleanup(struct lan743x_tx *tx)
{
	if (tx->head_cpu_ptr) {
		pci_free_consistent(tx->adapter->pdev,
				    sizeof(*tx->head_cpu_ptr),
				    (void *)(tx->head_cpu_ptr),
				    tx->head_dma_ptr);
		tx->head_cpu_ptr = NULL;
		tx->head_dma_ptr = 0;
	}
	kfree(tx->buffer_info);
	tx->buffer_info = NULL;

	if (tx->ring_cpu_ptr) {
		pci_free_consistent(tx->adapter->pdev,
				    tx->ring_allocation_size,
				    tx->ring_cpu_ptr,
				    tx->ring_dma_ptr);
		tx->ring_allocation_size = 0;
		tx->ring_cpu_ptr = NULL;
		tx->ring_dma_ptr = 0;
	}
	tx->ring_size = 0;
}