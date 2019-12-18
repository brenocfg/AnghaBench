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
struct tegra_uart_port {scalar_t__ rts_active; int /*<<< orphan*/  rx_cookie; int /*<<< orphan*/  rx_dma_chan; } ;
struct dma_tx_state {int /*<<< orphan*/  residue; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_tx_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_tx_state*) ; 
 int /*<<< orphan*/  set_rts (struct tegra_uart_port*,int) ; 
 int /*<<< orphan*/  tegra_uart_rx_buffer_push (struct tegra_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_uart_start_rx_dma (struct tegra_uart_port*) ; 

__attribute__((used)) static void tegra_uart_handle_rx_dma(struct tegra_uart_port *tup)
{
	struct dma_tx_state state;

	/* Deactivate flow control to stop sender */
	if (tup->rts_active)
		set_rts(tup, false);

	dmaengine_terminate_all(tup->rx_dma_chan);
	dmaengine_tx_status(tup->rx_dma_chan, tup->rx_cookie, &state);
	tegra_uart_rx_buffer_push(tup, state.residue);
	tegra_uart_start_rx_dma(tup);

	if (tup->rts_active)
		set_rts(tup, true);
}