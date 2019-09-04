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
typedef  int uint8_t ;
struct ishtp_device {void* ishtp_host_dma_tx_buf; int ishtp_dma_num_slots; int /*<<< orphan*/  ishtp_dma_tx_lock; scalar_t__* ishtp_dma_tx_map; int /*<<< orphan*/  devc; } ;

/* Variables and functions */
 int DMA_SLOT_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ishtp_cl_release_dma_acked_mem(struct ishtp_device *dev,
				    void *msg_addr,
				    uint8_t size)
{
	unsigned long	flags;
	int acked_slots = (size / DMA_SLOT_SIZE)
		+ 1 * (size % DMA_SLOT_SIZE != 0);
	int i, j;

	if ((msg_addr - dev->ishtp_host_dma_tx_buf) % DMA_SLOT_SIZE) {
		dev_err(dev->devc, "Bad DMA Tx ack address\n");
		return;
	}

	i = (msg_addr - dev->ishtp_host_dma_tx_buf) / DMA_SLOT_SIZE;
	spin_lock_irqsave(&dev->ishtp_dma_tx_lock, flags);
	for (j = 0; j < acked_slots; j++) {
		if ((i + j) >= dev->ishtp_dma_num_slots ||
					!dev->ishtp_dma_tx_map[i+j]) {
			/* no such slot, or memory is already free */
			spin_unlock_irqrestore(&dev->ishtp_dma_tx_lock, flags);
			dev_err(dev->devc, "Bad DMA Tx ack address\n");
			return;
		}
		dev->ishtp_dma_tx_map[i+j] = 0;
	}
	spin_unlock_irqrestore(&dev->ishtp_dma_tx_lock, flags);
}