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
struct irq_data {int dummy; } ;
struct gpio_chip {int dummy; } ;
struct cp2112_device {int gpio_poll; int /*<<< orphan*/  gpio_poll_worker; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp2112_gpio_irq_unmask (struct irq_data*) ; 
 int /*<<< orphan*/  cp2112_gpio_poll_callback ; 
 struct cp2112_device* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int cp2112_gpio_irq_startup(struct irq_data *d)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct cp2112_device *dev = gpiochip_get_data(gc);

	INIT_DELAYED_WORK(&dev->gpio_poll_worker, cp2112_gpio_poll_callback);

	if (!dev->gpio_poll) {
		dev->gpio_poll = true;
		schedule_delayed_work(&dev->gpio_poll_worker, 0);
	}

	cp2112_gpio_irq_unmask(d);
	return 0;
}