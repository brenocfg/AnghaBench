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
struct tty_port {int dummy; } ;
struct TYPE_4__ {TYPE_1__* state; } ;
struct tegra_uart_port {unsigned long ier_shadow; int /*<<< orphan*/  rx_cookie; scalar_t__ rx_dma_chan; int /*<<< orphan*/  use_rx_pio; scalar_t__ rx_in_progress; scalar_t__ rts_active; TYPE_2__ uport; } ;
struct dma_tx_state {int /*<<< orphan*/  residue; } ;
struct TYPE_3__ {struct tty_port port; } ;

/* Variables and functions */
 unsigned long TEGRA_UART_IER_EORD ; 
 int /*<<< orphan*/  UART_IER ; 
 unsigned long UART_IER_RDI ; 
 unsigned long UART_IER_RLSI ; 
 unsigned long UART_IER_RTOIE ; 
 int /*<<< orphan*/  dmaengine_terminate_all (scalar_t__) ; 
 int /*<<< orphan*/  dmaengine_tx_status (scalar_t__,int /*<<< orphan*/ ,struct dma_tx_state*) ; 
 int /*<<< orphan*/  set_rts (struct tegra_uart_port*,int) ; 
 int /*<<< orphan*/  tegra_uart_handle_rx_pio (struct tegra_uart_port*,struct tty_port*) ; 
 int /*<<< orphan*/  tegra_uart_rx_buffer_push (struct tegra_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_uart_wait_sym_time (struct tegra_uart_port*,int) ; 
 int /*<<< orphan*/  tegra_uart_write (struct tegra_uart_port*,unsigned long,int /*<<< orphan*/ ) ; 
 struct tegra_uart_port* to_tegra_uport (struct uart_port*) ; 

__attribute__((used)) static void tegra_uart_stop_rx(struct uart_port *u)
{
	struct tegra_uart_port *tup = to_tegra_uport(u);
	struct tty_port *port = &tup->uport.state->port;
	struct dma_tx_state state;
	unsigned long ier;

	if (tup->rts_active)
		set_rts(tup, false);

	if (!tup->rx_in_progress)
		return;

	tegra_uart_wait_sym_time(tup, 1); /* wait one character interval */

	ier = tup->ier_shadow;
	ier &= ~(UART_IER_RDI | UART_IER_RLSI | UART_IER_RTOIE |
					TEGRA_UART_IER_EORD);
	tup->ier_shadow = ier;
	tegra_uart_write(tup, ier, UART_IER);
	tup->rx_in_progress = 0;
	if (tup->rx_dma_chan && !tup->use_rx_pio) {
		dmaengine_terminate_all(tup->rx_dma_chan);
		dmaengine_tx_status(tup->rx_dma_chan, tup->rx_cookie, &state);
		tegra_uart_rx_buffer_push(tup, state.residue);
	} else {
		tegra_uart_handle_rx_pio(tup, port);
	}
}