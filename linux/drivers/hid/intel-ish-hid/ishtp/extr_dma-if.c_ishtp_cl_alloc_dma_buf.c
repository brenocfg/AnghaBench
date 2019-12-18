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
typedef  int /*<<< orphan*/  uint8_t ;
struct ishtp_device {int ishtp_host_dma_tx_buf_size; int ishtp_host_dma_rx_buf_size; int ishtp_dma_num_slots; void* ishtp_host_dma_rx_buf_phys; void* ishtp_host_dma_rx_buf; int /*<<< orphan*/  devc; int /*<<< orphan*/  ishtp_dma_tx_lock; int /*<<< orphan*/  ishtp_dma_tx_map; void* ishtp_host_dma_tx_buf_phys; void* ishtp_host_dma_tx_buf; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int DMA_SLOT_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,int,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void	ishtp_cl_alloc_dma_buf(struct ishtp_device *dev)
{
	dma_addr_t	h;

	if (dev->ishtp_host_dma_tx_buf)
		return;

	dev->ishtp_host_dma_tx_buf_size = 1024*1024;
	dev->ishtp_host_dma_rx_buf_size = 1024*1024;

	/* Allocate Tx buffer and init usage bitmap */
	dev->ishtp_host_dma_tx_buf = dma_alloc_coherent(dev->devc,
					dev->ishtp_host_dma_tx_buf_size,
					&h, GFP_KERNEL);
	if (dev->ishtp_host_dma_tx_buf)
		dev->ishtp_host_dma_tx_buf_phys = h;

	dev->ishtp_dma_num_slots = dev->ishtp_host_dma_tx_buf_size /
						DMA_SLOT_SIZE;

	dev->ishtp_dma_tx_map = kcalloc(dev->ishtp_dma_num_slots,
					sizeof(uint8_t),
					GFP_KERNEL);
	spin_lock_init(&dev->ishtp_dma_tx_lock);

	/* Allocate Rx buffer */
	dev->ishtp_host_dma_rx_buf = dma_alloc_coherent(dev->devc,
					dev->ishtp_host_dma_rx_buf_size,
					 &h, GFP_KERNEL);

	if (dev->ishtp_host_dma_rx_buf)
		dev->ishtp_host_dma_rx_buf_phys = h;
}