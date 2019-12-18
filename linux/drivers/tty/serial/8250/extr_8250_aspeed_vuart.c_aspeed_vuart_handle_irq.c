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
struct uart_port {TYPE_1__* state; struct aspeed_vuart* private_data; int /*<<< orphan*/  lock; } ;
struct uart_8250_port {int dummy; } ;
struct aspeed_vuart {int /*<<< orphan*/  unthrottle_timer; struct uart_8250_port* port; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IIR ; 
 unsigned int UART_IIR_NO_INT ; 
 int /*<<< orphan*/  UART_LSR ; 
 unsigned int UART_LSR_BI ; 
 unsigned int UART_LSR_DR ; 
 unsigned int UART_LSR_THRE ; 
 int /*<<< orphan*/  __aspeed_vuart_set_throttle (struct uart_8250_port*,int) ; 
 scalar_t__ jiffies ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  serial8250_modem_status (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_read_char (struct uart_8250_port*,unsigned int) ; 
 int /*<<< orphan*/  serial8250_tx_chars (struct uart_8250_port*) ; 
 unsigned int serial_in (struct uart_8250_port*,int /*<<< orphan*/ ) ; 
 unsigned int serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 
 int tty_buffer_space_avail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_unlock_and_check_sysrq (struct uart_port*,unsigned long) ; 
 scalar_t__ unthrottle_timeout ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

__attribute__((used)) static int aspeed_vuart_handle_irq(struct uart_port *port)
{
	struct uart_8250_port *up = up_to_u8250p(port);
	unsigned int iir, lsr;
	unsigned long flags;
	int space, count;

	iir = serial_port_in(port, UART_IIR);

	if (iir & UART_IIR_NO_INT)
		return 0;

	spin_lock_irqsave(&port->lock, flags);

	lsr = serial_port_in(port, UART_LSR);

	if (lsr & (UART_LSR_DR | UART_LSR_BI)) {
		space = tty_buffer_space_avail(&port->state->port);

		if (!space) {
			/* throttle and schedule an unthrottle later */
			struct aspeed_vuart *vuart = port->private_data;
			__aspeed_vuart_set_throttle(up, true);

			if (!timer_pending(&vuart->unthrottle_timer)) {
				vuart->port = up;
				mod_timer(&vuart->unthrottle_timer,
					  jiffies + unthrottle_timeout);
			}

		} else {
			count = min(space, 256);

			do {
				serial8250_read_char(up, lsr);
				lsr = serial_in(up, UART_LSR);
				if (--count == 0)
					break;
			} while (lsr & (UART_LSR_DR | UART_LSR_BI));

			tty_flip_buffer_push(&port->state->port);
		}
	}

	serial8250_modem_status(up);
	if (lsr & UART_LSR_THRE)
		serial8250_tx_chars(up);

	uart_unlock_and_check_sysrq(port, flags);

	return 1;
}