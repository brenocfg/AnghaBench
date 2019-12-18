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
struct uart_port {int /*<<< orphan*/  icount; TYPE_1__* state; struct mtk8250_data* private_data; } ;
struct uart_8250_port {int /*<<< orphan*/ * dma; } ;
struct mtk8250_data {int /*<<< orphan*/  rx_status; } ;
struct TYPE_2__ {int /*<<< orphan*/  xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RX_START ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int serial8250_do_startup (struct uart_port*) ; 
 int /*<<< orphan*/  uart_circ_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ uart_console (struct uart_port*) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

__attribute__((used)) static int mtk8250_startup(struct uart_port *port)
{
#ifdef CONFIG_SERIAL_8250_DMA
	struct uart_8250_port *up = up_to_u8250p(port);
	struct mtk8250_data *data = port->private_data;

	/* disable DMA for console */
	if (uart_console(port))
		up->dma = NULL;

	if (up->dma) {
		data->rx_status = DMA_RX_START;
		uart_circ_clear(&port->state->xmit);
	}
#endif
	memset(&port->icount, 0, sizeof(port->icount));

	return serial8250_do_startup(port);
}