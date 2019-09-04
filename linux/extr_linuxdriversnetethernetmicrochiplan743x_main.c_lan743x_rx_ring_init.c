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
struct sk_buff {int dummy; } ;
struct lan743x_rx_descriptor {int dummy; } ;
struct lan743x_rx_buffer_info {int dummy; } ;
struct lan743x_rx {int ring_size; size_t ring_allocation_size; int head_dma_ptr; scalar_t__ last_head; void* head_cpu_ptr; TYPE_1__* adapter; struct lan743x_rx_buffer_info* buffer_info; void* ring_dma_ptr; struct lan743x_rx_descriptor* ring_cpu_ptr; } ;
typedef  void* dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 size_t ALIGN (int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LAN743X_RX_RING_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int RX_CFG_B_RX_RING_LEN_MASK_ ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct sk_buff* lan743x_rx_allocate_skb (struct lan743x_rx*) ; 
 int lan743x_rx_init_ring_element (struct lan743x_rx*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  lan743x_rx_ring_cleanup (struct lan743x_rx*) ; 
 void* pci_zalloc_consistent (int /*<<< orphan*/ ,int,void**) ; 

__attribute__((used)) static int lan743x_rx_ring_init(struct lan743x_rx *rx)
{
	size_t ring_allocation_size = 0;
	dma_addr_t dma_ptr = 0;
	void *cpu_ptr = NULL;
	int ret = -ENOMEM;
	int index = 0;

	rx->ring_size = LAN743X_RX_RING_SIZE;
	if (rx->ring_size <= 1) {
		ret = -EINVAL;
		goto cleanup;
	}
	if (rx->ring_size & ~RX_CFG_B_RX_RING_LEN_MASK_) {
		ret = -EINVAL;
		goto cleanup;
	}
	ring_allocation_size = ALIGN(rx->ring_size *
				     sizeof(struct lan743x_rx_descriptor),
				     PAGE_SIZE);
	dma_ptr = 0;
	cpu_ptr = pci_zalloc_consistent(rx->adapter->pdev,
					ring_allocation_size, &dma_ptr);
	if (!cpu_ptr) {
		ret = -ENOMEM;
		goto cleanup;
	}
	rx->ring_allocation_size = ring_allocation_size;
	rx->ring_cpu_ptr = (struct lan743x_rx_descriptor *)cpu_ptr;
	rx->ring_dma_ptr = dma_ptr;

	cpu_ptr = kcalloc(rx->ring_size, sizeof(*rx->buffer_info),
			  GFP_KERNEL);
	if (!cpu_ptr) {
		ret = -ENOMEM;
		goto cleanup;
	}
	rx->buffer_info = (struct lan743x_rx_buffer_info *)cpu_ptr;
	dma_ptr = 0;
	cpu_ptr = pci_zalloc_consistent(rx->adapter->pdev,
					sizeof(*rx->head_cpu_ptr), &dma_ptr);
	if (!cpu_ptr) {
		ret = -ENOMEM;
		goto cleanup;
	}

	rx->head_cpu_ptr = cpu_ptr;
	rx->head_dma_ptr = dma_ptr;
	if (rx->head_dma_ptr & 0x3) {
		ret = -ENOMEM;
		goto cleanup;
	}

	rx->last_head = 0;
	for (index = 0; index < rx->ring_size; index++) {
		struct sk_buff *new_skb = lan743x_rx_allocate_skb(rx);

		ret = lan743x_rx_init_ring_element(rx, index, new_skb);
		if (ret)
			goto cleanup;
	}
	return 0;

cleanup:
	lan743x_rx_ring_cleanup(rx);
	return ret;
}