#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int dummy; } ;
struct TYPE_3__ {TYPE_2__* state; } ;
struct tegra_uart_port {scalar_t__ tx_in_progress; unsigned int tx_bytes_requested; int /*<<< orphan*/  tx_dma_desc; int /*<<< orphan*/  tx_cookie; int /*<<< orphan*/  tx_dma_chan; TYPE_1__ uport; } ;
struct dma_tx_state {unsigned int residue; } ;
struct circ_buf {unsigned int tail; } ;
struct TYPE_4__ {struct circ_buf xmit; } ;

/* Variables and functions */
 scalar_t__ TEGRA_UART_TX_DMA ; 
 int UART_XMIT_SIZE ; 
 int /*<<< orphan*/  async_tx_ack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_tx_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_tx_state*) ; 
 struct tegra_uart_port* to_tegra_uport (struct uart_port*) ; 

__attribute__((used)) static void tegra_uart_stop_tx(struct uart_port *u)
{
	struct tegra_uart_port *tup = to_tegra_uport(u);
	struct circ_buf *xmit = &tup->uport.state->xmit;
	struct dma_tx_state state;
	unsigned int count;

	if (tup->tx_in_progress != TEGRA_UART_TX_DMA)
		return;

	dmaengine_terminate_all(tup->tx_dma_chan);
	dmaengine_tx_status(tup->tx_dma_chan, tup->tx_cookie, &state);
	count = tup->tx_bytes_requested - state.residue;
	async_tx_ack(tup->tx_dma_desc);
	xmit->tail = (xmit->tail + count) & (UART_XMIT_SIZE - 1);
	tup->tx_in_progress = 0;
}