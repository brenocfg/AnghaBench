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
struct gpio_rcar_priv {int /*<<< orphan*/  wakeup_path; scalar_t__ irq_parent; int /*<<< orphan*/  dev; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 struct gpio_rcar_priv* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int irq_set_irq_wake (scalar_t__,unsigned int) ; 

__attribute__((used)) static int gpio_rcar_irq_set_wake(struct irq_data *d, unsigned int on)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct gpio_rcar_priv *p = gpiochip_get_data(gc);
	int error;

	if (p->irq_parent) {
		error = irq_set_irq_wake(p->irq_parent, on);
		if (error) {
			dev_dbg(p->dev, "irq %u doesn't support irq_set_wake\n",
				p->irq_parent);
			p->irq_parent = 0;
		}
	}

	if (on)
		atomic_inc(&p->wakeup_path);
	else
		atomic_dec(&p->wakeup_path);

	return 0;
}