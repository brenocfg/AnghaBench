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
typedef  int u32 ;
struct u300_gpio_port {int /*<<< orphan*/  name; } ;
struct u300_gpio {int /*<<< orphan*/  dev; struct u300_gpio_port* ports; } ;
struct irq_data {int hwirq; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int U300_PIN_BIT (int) ; 
 int /*<<< orphan*/  U300_PIN_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 
 struct u300_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  ien ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void u300_gpio_irq_enable(struct irq_data *d)
{
	struct gpio_chip *chip = irq_data_get_irq_chip_data(d);
	struct u300_gpio *gpio = gpiochip_get_data(chip);
	struct u300_gpio_port *port = &gpio->ports[d->hwirq >> 3];
	int offset = d->hwirq;
	u32 val;
	unsigned long flags;

	dev_dbg(gpio->dev, "enable IRQ for hwirq %lu on port %s, offset %d\n",
		 d->hwirq, port->name, offset);
	local_irq_save(flags);
	val = readl(U300_PIN_REG(offset, ien));
	writel(val | U300_PIN_BIT(offset), U300_PIN_REG(offset, ien));
	local_irq_restore(flags);
}