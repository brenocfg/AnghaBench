#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct uart_8250_port {TYPE_2__ port; struct uart_8250_dma* dma; } ;
struct uart_8250_dma {scalar_t__ tx_running; TYPE_3__* txchan; int /*<<< orphan*/  tx_addr; TYPE_3__* rxchan; int /*<<< orphan*/  rx_addr; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  rx_size; } ;
struct TYPE_7__ {TYPE_1__* device; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  UART_XMIT_SIZE ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (TYPE_3__*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_sync (TYPE_3__*) ; 

void serial8250_release_dma(struct uart_8250_port *p)
{
	struct uart_8250_dma *dma = p->dma;

	if (!dma)
		return;

	/* Release RX resources */
	dmaengine_terminate_sync(dma->rxchan);
	dma_free_coherent(dma->rxchan->device->dev, dma->rx_size, dma->rx_buf,
			  dma->rx_addr);
	dma_release_channel(dma->rxchan);
	dma->rxchan = NULL;

	/* Release TX resources */
	dmaengine_terminate_sync(dma->txchan);
	dma_unmap_single(dma->txchan->device->dev, dma->tx_addr,
			 UART_XMIT_SIZE, DMA_TO_DEVICE);
	dma_release_channel(dma->txchan);
	dma->txchan = NULL;
	dma->tx_running = 0;

	dev_dbg_ratelimited(p->port.dev, "dma channels released\n");
}