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
struct tty_struct {struct sdio_uart_port* driver_data; } ;
struct sdio_uart_port {char x_char; int ier; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int UART_IER_THRI ; 
 scalar_t__ sdio_uart_claim_func (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  sdio_uart_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_uart_release_func (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  sdio_uart_start_tx (struct sdio_uart_port*) ; 

__attribute__((used)) static void sdio_uart_send_xchar(struct tty_struct *tty, char ch)
{
	struct sdio_uart_port *port = tty->driver_data;

	port->x_char = ch;
	if (ch && !(port->ier & UART_IER_THRI)) {
		if (sdio_uart_claim_func(port) != 0)
			return;
		sdio_uart_start_tx(port);
		sdio_uart_irq(port->func);
		sdio_uart_release_func(port);
	}
}