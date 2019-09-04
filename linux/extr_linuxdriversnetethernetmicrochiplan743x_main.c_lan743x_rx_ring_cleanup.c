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
struct lan743x_rx {int ring_size; int ring_allocation_size; scalar_t__ last_head; scalar_t__ ring_dma_ptr; int /*<<< orphan*/ * ring_cpu_ptr; TYPE_1__* adapter; int /*<<< orphan*/ * buffer_info; scalar_t__ head_dma_ptr; int /*<<< orphan*/ * head_cpu_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lan743x_rx_release_ring_element (struct lan743x_rx*,int) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void lan743x_rx_ring_cleanup(struct lan743x_rx *rx)
{
	if (rx->buffer_info && rx->ring_cpu_ptr) {
		int index;

		for (index = 0; index < rx->ring_size; index++)
			lan743x_rx_release_ring_element(rx, index);
	}

	if (rx->head_cpu_ptr) {
		pci_free_consistent(rx->adapter->pdev,
				    sizeof(*rx->head_cpu_ptr),
				    rx->head_cpu_ptr,
				    rx->head_dma_ptr);
		rx->head_cpu_ptr = NULL;
		rx->head_dma_ptr = 0;
	}

	kfree(rx->buffer_info);
	rx->buffer_info = NULL;

	if (rx->ring_cpu_ptr) {
		pci_free_consistent(rx->adapter->pdev,
				    rx->ring_allocation_size,
				    rx->ring_cpu_ptr,
				    rx->ring_dma_ptr);
		rx->ring_allocation_size = 0;
		rx->ring_cpu_ptr = NULL;
		rx->ring_dma_ptr = 0;
	}

	rx->ring_size = 0;
	rx->last_head = 0;
}