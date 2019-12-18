#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct s3c24xx_uart_port {TYPE_1__ port; struct s3c24xx_uart_dma* dma; } ;
struct s3c24xx_uart_dma {int /*<<< orphan*/  rx_chan; TYPE_2__* rx_desc; int /*<<< orphan*/  rx_cookie; int /*<<< orphan*/  rx_size; int /*<<< orphan*/  rx_bytes_requested; int /*<<< orphan*/  rx_addr; } ;
struct TYPE_5__ {struct s3c24xx_uart_port* callback_param; int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* dmaengine_prep_slave_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_submit (TYPE_2__*) ; 
 int /*<<< orphan*/  s3c24xx_serial_rx_dma_complete ; 

__attribute__((used)) static void s3c64xx_start_rx_dma(struct s3c24xx_uart_port *ourport)
{
	struct s3c24xx_uart_dma *dma = ourport->dma;

	dma_sync_single_for_device(ourport->port.dev, dma->rx_addr,
				dma->rx_size, DMA_FROM_DEVICE);

	dma->rx_desc = dmaengine_prep_slave_single(dma->rx_chan,
				dma->rx_addr, dma->rx_size, DMA_DEV_TO_MEM,
				DMA_PREP_INTERRUPT);
	if (!dma->rx_desc) {
		dev_err(ourport->port.dev, "Unable to get desc for Rx\n");
		return;
	}

	dma->rx_desc->callback = s3c24xx_serial_rx_dma_complete;
	dma->rx_desc->callback_param = ourport;
	dma->rx_bytes_requested = dma->rx_size;

	dma->rx_cookie = dmaengine_submit(dma->rx_desc);
	dma_async_issue_pending(dma->rx_chan);
}