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
struct xlp_gpio_priv {int /*<<< orphan*/  gpio_intr_pol; int /*<<< orphan*/  gpio_intr_type; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 int XLP_GPIO_IRQ_POL_HIGH ; 
 int XLP_GPIO_IRQ_POL_LOW ; 
 int XLP_GPIO_IRQ_TYPE_EDGE ; 
 int XLP_GPIO_IRQ_TYPE_LVL ; 
 struct xlp_gpio_priv* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  xlp_gpio_set_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xlp_gpio_set_irq_type(struct irq_data *d, unsigned int type)
{
	struct gpio_chip *gc  = irq_data_get_irq_chip_data(d);
	struct xlp_gpio_priv *priv = gpiochip_get_data(gc);
	int pol, irq_type;

	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
		irq_type = XLP_GPIO_IRQ_TYPE_EDGE;
		pol = XLP_GPIO_IRQ_POL_HIGH;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		irq_type = XLP_GPIO_IRQ_TYPE_EDGE;
		pol = XLP_GPIO_IRQ_POL_LOW;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		irq_type = XLP_GPIO_IRQ_TYPE_LVL;
		pol = XLP_GPIO_IRQ_POL_HIGH;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		irq_type = XLP_GPIO_IRQ_TYPE_LVL;
		pol = XLP_GPIO_IRQ_POL_LOW;
		break;
	default:
		return -EINVAL;
	}

	xlp_gpio_set_reg(priv->gpio_intr_type, d->hwirq, irq_type);
	xlp_gpio_set_reg(priv->gpio_intr_pol, d->hwirq, pol);

	return 0;
}