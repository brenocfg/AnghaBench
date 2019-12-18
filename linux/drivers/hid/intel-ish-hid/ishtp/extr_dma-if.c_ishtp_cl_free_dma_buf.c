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
struct ishtp_device {int /*<<< orphan*/ * ishtp_dma_tx_map; int /*<<< orphan*/ * ishtp_host_dma_rx_buf; int /*<<< orphan*/ * ishtp_host_dma_tx_buf; int /*<<< orphan*/  ishtp_host_dma_rx_buf_size; int /*<<< orphan*/  devc; int /*<<< orphan*/  ishtp_host_dma_rx_buf_phys; int /*<<< orphan*/  ishtp_host_dma_tx_buf_size; int /*<<< orphan*/  ishtp_host_dma_tx_buf_phys; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void	ishtp_cl_free_dma_buf(struct ishtp_device *dev)
{
	dma_addr_t	h;

	if (dev->ishtp_host_dma_tx_buf) {
		h = dev->ishtp_host_dma_tx_buf_phys;
		dma_free_coherent(dev->devc, dev->ishtp_host_dma_tx_buf_size,
				  dev->ishtp_host_dma_tx_buf, h);
	}

	if (dev->ishtp_host_dma_rx_buf) {
		h = dev->ishtp_host_dma_rx_buf_phys;
		dma_free_coherent(dev->devc, dev->ishtp_host_dma_rx_buf_size,
				  dev->ishtp_host_dma_rx_buf, h);
	}

	kfree(dev->ishtp_dma_tx_map);
	dev->ishtp_host_dma_tx_buf = NULL;
	dev->ishtp_host_dma_rx_buf = NULL;
	dev->ishtp_dma_tx_map = NULL;
}