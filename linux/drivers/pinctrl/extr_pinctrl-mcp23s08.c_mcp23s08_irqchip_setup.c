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
struct gpio_chip {int /*<<< orphan*/  parent; } ;
struct mcp23s08 {int /*<<< orphan*/  irq; int /*<<< orphan*/  irq_chip; struct gpio_chip chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int gpiochip_irqchip_add_nested (struct gpio_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_set_nested_irqchip (struct gpio_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_simple_irq ; 

__attribute__((used)) static int mcp23s08_irqchip_setup(struct mcp23s08 *mcp)
{
	struct gpio_chip *chip = &mcp->chip;
	int err;

	err =  gpiochip_irqchip_add_nested(chip,
					   &mcp->irq_chip,
					   0,
					   handle_simple_irq,
					   IRQ_TYPE_NONE);
	if (err) {
		dev_err(chip->parent,
			"could not connect irqchip to gpiochip: %d\n", err);
		return err;
	}

	gpiochip_set_nested_irqchip(chip,
				    &mcp->irq_chip,
				    mcp->irq);

	return 0;
}