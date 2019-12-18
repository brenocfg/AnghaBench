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
struct TYPE_6__ {int /*<<< orphan*/  dev; TYPE_1__* state; } ;
struct tegra_uart_port {unsigned long tx_bytes; unsigned long tx_bytes_requested; int /*<<< orphan*/  tx_dma_chan; TYPE_3__* tx_dma_desc; int /*<<< orphan*/  tx_cookie; int /*<<< orphan*/  tx_in_progress; TYPE_2__ uport; scalar_t__ tx_dma_buf_phys; } ;
struct circ_buf {scalar_t__ tail; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_7__ {struct tegra_uart_port* callback_param; int /*<<< orphan*/  callback; } ;
struct TYPE_5__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EIO ; 
 int /*<<< orphan*/  TEGRA_UART_TX_DMA ; 
 int /*<<< orphan*/  UART_XMIT_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* dmaengine_prep_slave_single (int /*<<< orphan*/ ,scalar_t__,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_submit (TYPE_3__*) ; 
 int /*<<< orphan*/  tegra_uart_tx_dma_complete ; 

__attribute__((used)) static int tegra_uart_start_tx_dma(struct tegra_uart_port *tup,
		unsigned long count)
{
	struct circ_buf *xmit = &tup->uport.state->xmit;
	dma_addr_t tx_phys_addr;

	dma_sync_single_for_device(tup->uport.dev, tup->tx_dma_buf_phys,
				UART_XMIT_SIZE, DMA_TO_DEVICE);

	tup->tx_bytes = count & ~(0xF);
	tx_phys_addr = tup->tx_dma_buf_phys + xmit->tail;
	tup->tx_dma_desc = dmaengine_prep_slave_single(tup->tx_dma_chan,
				tx_phys_addr, tup->tx_bytes, DMA_MEM_TO_DEV,
				DMA_PREP_INTERRUPT);
	if (!tup->tx_dma_desc) {
		dev_err(tup->uport.dev, "Not able to get desc for Tx\n");
		return -EIO;
	}

	tup->tx_dma_desc->callback = tegra_uart_tx_dma_complete;
	tup->tx_dma_desc->callback_param = tup;
	tup->tx_in_progress = TEGRA_UART_TX_DMA;
	tup->tx_bytes_requested = tup->tx_bytes;
	tup->tx_cookie = dmaengine_submit(tup->tx_dma_desc);
	dma_async_issue_pending(tup->tx_dma_chan);
	return 0;
}