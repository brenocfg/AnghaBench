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
struct mxs_auart_port {int ms_irq_enabled; scalar_t__* gpio_irq; } ;

/* Variables and functions */
 size_t UART_GPIO_CTS ; 
 size_t UART_GPIO_DCD ; 
 size_t UART_GPIO_DSR ; 
 size_t UART_GPIO_RI ; 
 int /*<<< orphan*/  disable_irq (scalar_t__) ; 
 struct mxs_auart_port* to_auart_port (struct uart_port*) ; 

__attribute__((used)) static void mxs_auart_disable_ms(struct uart_port *port)
{
	struct mxs_auart_port *s = to_auart_port(port);

	/*
	 * Interrupt should not be disabled twice
	 */
	if (!s->ms_irq_enabled)
		return;

	s->ms_irq_enabled = false;

	if (s->gpio_irq[UART_GPIO_CTS] >= 0)
		disable_irq(s->gpio_irq[UART_GPIO_CTS]);
	/* TODO: disable AUART_INTR_CTSMIEN otherwise */

	if (s->gpio_irq[UART_GPIO_DSR] >= 0)
		disable_irq(s->gpio_irq[UART_GPIO_DSR]);

	if (s->gpio_irq[UART_GPIO_RI] >= 0)
		disable_irq(s->gpio_irq[UART_GPIO_RI]);

	if (s->gpio_irq[UART_GPIO_DCD] >= 0)
		disable_irq(s->gpio_irq[UART_GPIO_DCD]);
}