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
struct uart_port {struct mtk8250_data* private_data; } ;
struct uart_8250_port {scalar_t__ dma; } ;
struct mtk8250_data {int /*<<< orphan*/  rx_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RX_SHUTDOWN ; 
 void serial8250_do_shutdown (struct uart_port*) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

__attribute__((used)) static void mtk8250_shutdown(struct uart_port *port)
{
#ifdef CONFIG_SERIAL_8250_DMA
	struct uart_8250_port *up = up_to_u8250p(port);
	struct mtk8250_data *data = port->private_data;

	if (up->dma)
		data->rx_status = DMA_RX_SHUTDOWN;
#endif

	return serial8250_do_shutdown(port);
}