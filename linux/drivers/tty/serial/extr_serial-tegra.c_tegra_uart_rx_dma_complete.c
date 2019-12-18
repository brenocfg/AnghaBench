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
struct uart_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct tegra_uart_port {scalar_t__ rts_active; struct uart_port uport; int /*<<< orphan*/  rx_cookie; int /*<<< orphan*/  rx_dma_chan; } ;
struct dma_tx_state {int dummy; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;

/* Variables and functions */
 int DMA_IN_PROGRESS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int dmaengine_tx_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_tx_state*) ; 
 int /*<<< orphan*/  set_rts (struct tegra_uart_port*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tegra_uart_rx_buffer_push (struct tegra_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_uart_start_rx_dma (struct tegra_uart_port*) ; 

__attribute__((used)) static void tegra_uart_rx_dma_complete(void *args)
{
	struct tegra_uart_port *tup = args;
	struct uart_port *u = &tup->uport;
	unsigned long flags;
	struct dma_tx_state state;
	enum dma_status status;

	spin_lock_irqsave(&u->lock, flags);

	status = dmaengine_tx_status(tup->rx_dma_chan, tup->rx_cookie, &state);

	if (status == DMA_IN_PROGRESS) {
		dev_dbg(tup->uport.dev, "RX DMA is in progress\n");
		goto done;
	}

	/* Deactivate flow control to stop sender */
	if (tup->rts_active)
		set_rts(tup, false);

	tegra_uart_rx_buffer_push(tup, 0);
	tegra_uart_start_rx_dma(tup);

	/* Activate flow control to start transfer */
	if (tup->rts_active)
		set_rts(tup, true);

done:
	spin_unlock_irqrestore(&u->lock, flags);
}