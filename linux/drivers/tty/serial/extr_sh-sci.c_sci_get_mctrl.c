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
struct sci_port {scalar_t__ autorts; struct mctrl_gpios* gpios; } ;
struct mctrl_gpios {int dummy; } ;

/* Variables and functions */
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 int /*<<< orphan*/  UART_GPIO_CTS ; 
 int /*<<< orphan*/  UART_GPIO_DCD ; 
 int /*<<< orphan*/  UART_GPIO_DSR ; 
 int /*<<< orphan*/  mctrl_gpio_get (struct mctrl_gpios*,unsigned int*) ; 
 int /*<<< orphan*/  mctrl_gpio_to_gpiod (struct mctrl_gpios*,int /*<<< orphan*/ ) ; 
 scalar_t__ sci_get_cts (struct uart_port*) ; 
 struct sci_port* to_sci_port (struct uart_port*) ; 

__attribute__((used)) static unsigned int sci_get_mctrl(struct uart_port *port)
{
	struct sci_port *s = to_sci_port(port);
	struct mctrl_gpios *gpios = s->gpios;
	unsigned int mctrl = 0;

	mctrl_gpio_get(gpios, &mctrl);

	/*
	 * CTS/RTS is handled in hardware when supported, while nothing
	 * else is wired up.
	 */
	if (s->autorts) {
		if (sci_get_cts(port))
			mctrl |= TIOCM_CTS;
	} else if (!mctrl_gpio_to_gpiod(gpios, UART_GPIO_CTS)) {
		mctrl |= TIOCM_CTS;
	}
	if (!mctrl_gpio_to_gpiod(gpios, UART_GPIO_DSR))
		mctrl |= TIOCM_DSR;
	if (!mctrl_gpio_to_gpiod(gpios, UART_GPIO_DCD))
		mctrl |= TIOCM_CAR;

	return mctrl;
}