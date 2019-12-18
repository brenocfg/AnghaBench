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
struct TYPE_2__ {int flags; scalar_t__ delay_rts_before_send; } ;
struct uart_port {TYPE_1__ rs485; } ;
struct uart_omap_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  rts_gpio; int /*<<< orphan*/  scr; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_UART_SCR_TX_EMPTY ; 
 int SER_RS485_ENABLED ; 
 int SER_RS485_RTS_ON_SEND ; 
 int SER_RS485_RX_DURING_TX ; 
 int /*<<< orphan*/  UART_OMAP_SCR ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_omap_enable_ier_thri (struct uart_omap_port*) ; 
 int /*<<< orphan*/  serial_omap_stop_rx (struct uart_port*) ; 
 int /*<<< orphan*/  serial_out (struct uart_omap_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct uart_omap_port* to_uart_omap_port (struct uart_port*) ; 

__attribute__((used)) static void serial_omap_start_tx(struct uart_port *port)
{
	struct uart_omap_port *up = to_uart_omap_port(port);
	int res;

	pm_runtime_get_sync(up->dev);

	/* Handle RS-485 */
	if (port->rs485.flags & SER_RS485_ENABLED) {
		/* Fire THR interrupts when FIFO is below trigger level */
		up->scr &= ~OMAP_UART_SCR_TX_EMPTY;
		serial_out(up, UART_OMAP_SCR, up->scr);

		/* if rts not already enabled */
		res = (port->rs485.flags & SER_RS485_RTS_ON_SEND) ? 1 : 0;
		if (gpio_get_value(up->rts_gpio) != res) {
			gpio_set_value(up->rts_gpio, res);
			if (port->rs485.delay_rts_before_send > 0)
				mdelay(port->rs485.delay_rts_before_send);
		}
	}

	if ((port->rs485.flags & SER_RS485_ENABLED) &&
	    !(port->rs485.flags & SER_RS485_RX_DURING_TX))
		serial_omap_stop_rx(port);

	serial_omap_enable_ier_thri(up);
	pm_runtime_mark_last_busy(up->dev);
	pm_runtime_put_autosuspend(up->dev);
}