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
struct uart_port {int dummy; } ;
struct tegra_uart_port {scalar_t__ tx_dma_chan; scalar_t__ tx_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmaengine_terminate_all (scalar_t__) ; 
 struct tegra_uart_port* to_tegra_uport (struct uart_port*) ; 

__attribute__((used)) static void tegra_uart_flush_buffer(struct uart_port *u)
{
	struct tegra_uart_port *tup = to_tegra_uport(u);

	tup->tx_bytes = 0;
	if (tup->tx_dma_chan)
		dmaengine_terminate_all(tup->tx_dma_chan);
}