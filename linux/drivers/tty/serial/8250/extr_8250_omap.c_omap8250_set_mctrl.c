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
typedef  int /*<<< orphan*/  u8 ;
struct uart_port {int status; } ;
struct TYPE_2__ {struct omap8250_priv* private_data; } ;
struct uart_8250_port {int /*<<< orphan*/  gpios; TYPE_1__ port; } ;
struct omap8250_priv {int /*<<< orphan*/  efr; } ;

/* Variables and functions */
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  UART_EFR ; 
 int /*<<< orphan*/  UART_EFR_RTS ; 
 int /*<<< orphan*/  UART_GPIO_RTS ; 
 int /*<<< orphan*/  UART_LCR ; 
 int /*<<< orphan*/  UART_LCR_CONF_MODE_B ; 
 int UPSTAT_AUTORTS ; 
 int /*<<< orphan*/  mctrl_gpio_to_gpiod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial8250_do_set_mctrl (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  serial_in (struct uart_8250_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_8250_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

__attribute__((used)) static void omap8250_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	struct uart_8250_port *up = up_to_u8250p(port);
	struct omap8250_priv *priv = up->port.private_data;
	u8 lcr;

	serial8250_do_set_mctrl(port, mctrl);

	if (!mctrl_gpio_to_gpiod(up->gpios, UART_GPIO_RTS)) {
		/*
		 * Turn off autoRTS if RTS is lowered and restore autoRTS
		 * setting if RTS is raised
		 */
		lcr = serial_in(up, UART_LCR);
		serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
		if ((mctrl & TIOCM_RTS) && (port->status & UPSTAT_AUTORTS))
			priv->efr |= UART_EFR_RTS;
		else
			priv->efr &= ~UART_EFR_RTS;
		serial_out(up, UART_EFR, priv->efr);
		serial_out(up, UART_LCR, lcr);
	}
}