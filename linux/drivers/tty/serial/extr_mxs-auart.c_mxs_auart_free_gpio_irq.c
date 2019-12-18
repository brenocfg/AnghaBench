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
struct mxs_auart_port {scalar_t__* gpio_irq; } ;
typedef  enum mctrl_gpio_idx { ____Placeholder_mctrl_gpio_idx } mctrl_gpio_idx ;

/* Variables and functions */
 int UART_GPIO_MAX ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct mxs_auart_port*) ; 

__attribute__((used)) static void mxs_auart_free_gpio_irq(struct mxs_auart_port *s)
{
	enum mctrl_gpio_idx i;

	for (i = 0; i < UART_GPIO_MAX; i++)
		if (s->gpio_irq[i] >= 0)
			free_irq(s->gpio_irq[i], s);
}