#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct pistachio_pinctrl {unsigned int nbanks; struct pistachio_gpio_bank* gpio_banks; TYPE_6__* dev; scalar_t__ base; } ;
struct TYPE_8__ {struct device_node* of_node; TYPE_6__* parent; } ;
struct pistachio_gpio_bank {TYPE_1__ gpio_chip; int /*<<< orphan*/  npins; int /*<<< orphan*/  pin_base; int /*<<< orphan*/  irq_chip; scalar_t__ base; struct pistachio_pinctrl* pctl; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  child_name ;
struct TYPE_9__ {struct device_node* of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ GPIO_BANK_BASE (unsigned int) ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_6__*) ; 
 int gpiochip_add_data (TYPE_1__*,struct pistachio_gpio_bank*) ; 
 int gpiochip_add_pin_range (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpiochip_irqchip_add (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  gpiochip_set_chained_irqchip (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  pistachio_gpio_irq_handler ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static int pistachio_gpio_register(struct pistachio_pinctrl *pctl)
{
	struct device_node *node = pctl->dev->of_node;
	struct pistachio_gpio_bank *bank;
	unsigned int i;
	int irq, ret = 0;

	for (i = 0; i < pctl->nbanks; i++) {
		char child_name[sizeof("gpioXX")];
		struct device_node *child;

		snprintf(child_name, sizeof(child_name), "gpio%d", i);
		child = of_get_child_by_name(node, child_name);
		if (!child) {
			dev_err(pctl->dev, "No node for bank %u\n", i);
			ret = -ENODEV;
			goto err;
		}

		if (!of_find_property(child, "gpio-controller", NULL)) {
			dev_err(pctl->dev,
				"No gpio-controller property for bank %u\n", i);
			of_node_put(child);
			ret = -ENODEV;
			goto err;
		}

		irq = irq_of_parse_and_map(child, 0);
		if (irq < 0) {
			dev_err(pctl->dev, "No IRQ for bank %u: %d\n", i, irq);
			of_node_put(child);
			ret = irq;
			goto err;
		}

		bank = &pctl->gpio_banks[i];
		bank->pctl = pctl;
		bank->base = pctl->base + GPIO_BANK_BASE(i);

		bank->gpio_chip.parent = pctl->dev;
		bank->gpio_chip.of_node = child;
		ret = gpiochip_add_data(&bank->gpio_chip, bank);
		if (ret < 0) {
			dev_err(pctl->dev, "Failed to add GPIO chip %u: %d\n",
				i, ret);
			goto err;
		}

		ret = gpiochip_irqchip_add(&bank->gpio_chip, &bank->irq_chip,
					   0, handle_level_irq, IRQ_TYPE_NONE);
		if (ret < 0) {
			dev_err(pctl->dev, "Failed to add IRQ chip %u: %d\n",
				i, ret);
			gpiochip_remove(&bank->gpio_chip);
			goto err;
		}
		gpiochip_set_chained_irqchip(&bank->gpio_chip, &bank->irq_chip,
					     irq, pistachio_gpio_irq_handler);

		ret = gpiochip_add_pin_range(&bank->gpio_chip,
					     dev_name(pctl->dev), 0,
					     bank->pin_base, bank->npins);
		if (ret < 0) {
			dev_err(pctl->dev, "Failed to add GPIO range %u: %d\n",
				i, ret);
			gpiochip_remove(&bank->gpio_chip);
			goto err;
		}
	}

	return 0;
err:
	for (; i > 0; i--) {
		bank = &pctl->gpio_banks[i - 1];
		gpiochip_remove(&bank->gpio_chip);
	}
	return ret;
}