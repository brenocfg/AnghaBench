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
struct platform_device {int dummy; } ;
struct irq_data {int dummy; } ;
struct gpio_chip {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq_wake (int) ; 
 int /*<<< orphan*/  enable_irq_wake (int) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int int0002_irq_set_wake(struct irq_data *data, unsigned int on)
{
	struct gpio_chip *chip = irq_data_get_irq_chip_data(data);
	struct platform_device *pdev = to_platform_device(chip->parent);
	int irq = platform_get_irq(pdev, 0);

	/* Propagate to parent irq */
	if (on)
		enable_irq_wake(irq);
	else
		disable_irq_wake(irq);

	return 0;
}