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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct tegra_uart_port {int /*<<< orphan*/ * tx_dma_buf_virt; scalar_t__ tx_dma_buf_phys; int /*<<< orphan*/ * tx_dma_chan; TYPE_1__ uport; int /*<<< orphan*/ * rx_dma_buf_virt; scalar_t__ rx_dma_buf_phys; int /*<<< orphan*/ * rx_dma_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  TEGRA_UART_RX_DMA_BUFFER_SIZE ; 
 int /*<<< orphan*/  UART_XMIT_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tegra_uart_dma_channel_free(struct tegra_uart_port *tup,
		bool dma_to_memory)
{
	if (dma_to_memory) {
		dmaengine_terminate_all(tup->rx_dma_chan);
		dma_release_channel(tup->rx_dma_chan);
		dma_free_coherent(tup->uport.dev, TEGRA_UART_RX_DMA_BUFFER_SIZE,
				tup->rx_dma_buf_virt, tup->rx_dma_buf_phys);
		tup->rx_dma_chan = NULL;
		tup->rx_dma_buf_phys = 0;
		tup->rx_dma_buf_virt = NULL;
	} else {
		dmaengine_terminate_all(tup->tx_dma_chan);
		dma_release_channel(tup->tx_dma_chan);
		dma_unmap_single(tup->uport.dev, tup->tx_dma_buf_phys,
			UART_XMIT_SIZE, DMA_TO_DEVICE);
		tup->tx_dma_chan = NULL;
		tup->tx_dma_buf_phys = 0;
		tup->tx_dma_buf_virt = NULL;
	}
}