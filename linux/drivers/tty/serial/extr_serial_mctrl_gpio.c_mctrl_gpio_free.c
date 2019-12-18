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
struct mctrl_gpios {scalar_t__* gpio; scalar_t__* irq; TYPE_1__* port; } ;
struct device {int dummy; } ;
typedef  enum mctrl_gpio_idx { ____Placeholder_mctrl_gpio_idx } mctrl_gpio_idx ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int UART_GPIO_MAX ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,scalar_t__,struct mctrl_gpios*) ; 
 int /*<<< orphan*/  devm_gpiod_put (struct device*,scalar_t__) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct mctrl_gpios*) ; 

void mctrl_gpio_free(struct device *dev, struct mctrl_gpios *gpios)
{
	enum mctrl_gpio_idx i;

	if (gpios == NULL)
		return;

	for (i = 0; i < UART_GPIO_MAX; i++) {
		if (gpios->irq[i])
			devm_free_irq(gpios->port->dev, gpios->irq[i], gpios);

		if (gpios->gpio[i])
			devm_gpiod_put(dev, gpios->gpio[i]);
	}
	devm_kfree(dev, gpios);
}