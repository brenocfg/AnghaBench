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
typedef  int /*<<< orphan*/  uint32_t ;
struct uart_port {int dummy; } ;
struct atmel_uart_port {int ms_irq_enabled; int /*<<< orphan*/  gpios; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_US_CTSIC ; 
 int /*<<< orphan*/  ATMEL_US_DCDIC ; 
 int /*<<< orphan*/  ATMEL_US_DSRIC ; 
 int /*<<< orphan*/  ATMEL_US_IER ; 
 int /*<<< orphan*/  ATMEL_US_RIIC ; 
 int /*<<< orphan*/  UART_GPIO_CTS ; 
 int /*<<< orphan*/  UART_GPIO_DCD ; 
 int /*<<< orphan*/  UART_GPIO_DSR ; 
 int /*<<< orphan*/  UART_GPIO_RI ; 
 int /*<<< orphan*/  atmel_uart_writel (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mctrl_gpio_enable_ms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mctrl_gpio_to_gpiod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static void atmel_enable_ms(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	uint32_t ier = 0;

	/*
	 * Interrupt should not be enabled twice
	 */
	if (atmel_port->ms_irq_enabled)
		return;

	atmel_port->ms_irq_enabled = true;

	if (!mctrl_gpio_to_gpiod(atmel_port->gpios, UART_GPIO_CTS))
		ier |= ATMEL_US_CTSIC;

	if (!mctrl_gpio_to_gpiod(atmel_port->gpios, UART_GPIO_DSR))
		ier |= ATMEL_US_DSRIC;

	if (!mctrl_gpio_to_gpiod(atmel_port->gpios, UART_GPIO_RI))
		ier |= ATMEL_US_RIIC;

	if (!mctrl_gpio_to_gpiod(atmel_port->gpios, UART_GPIO_DCD))
		ier |= ATMEL_US_DCDIC;

	atmel_uart_writel(port, ATMEL_US_IER, ier);

	mctrl_gpio_enable_ms(atmel_port->gpios);
}