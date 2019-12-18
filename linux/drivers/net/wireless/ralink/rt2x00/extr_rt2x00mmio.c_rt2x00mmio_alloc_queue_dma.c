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
struct rt2x00_dev {int /*<<< orphan*/  dev; } ;
struct queue_entry_priv_mmio {scalar_t__ desc_dma; void* desc; } ;
struct data_queue {int limit; int desc_size; TYPE_1__* entries; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {struct queue_entry_priv_mmio* priv_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2x00mmio_alloc_queue_dma(struct rt2x00_dev *rt2x00dev,
				      struct data_queue *queue)
{
	struct queue_entry_priv_mmio *entry_priv;
	void *addr;
	dma_addr_t dma;
	unsigned int i;

	/*
	 * Allocate DMA memory for descriptor and buffer.
	 */
	addr = dma_alloc_coherent(rt2x00dev->dev,
				  queue->limit * queue->desc_size, &dma,
				  GFP_KERNEL);
	if (!addr)
		return -ENOMEM;

	/*
	 * Initialize all queue entries to contain valid addresses.
	 */
	for (i = 0; i < queue->limit; i++) {
		entry_priv = queue->entries[i].priv_data;
		entry_priv->desc = addr + i * queue->desc_size;
		entry_priv->desc_dma = dma + i * queue->desc_size;
	}

	return 0;
}