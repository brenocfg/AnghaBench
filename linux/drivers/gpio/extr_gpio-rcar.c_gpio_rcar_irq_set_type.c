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
struct gpio_rcar_priv {int /*<<< orphan*/  has_both_edge_trigger; int /*<<< orphan*/  dev; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  gpio_rcar_config_interrupt_input_mode (struct gpio_rcar_priv*,unsigned int,int,int,int) ; 
 struct gpio_rcar_priv* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 unsigned int irqd_to_hwirq (struct irq_data*) ; 

__attribute__((used)) static int gpio_rcar_irq_set_type(struct irq_data *d, unsigned int type)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct gpio_rcar_priv *p = gpiochip_get_data(gc);
	unsigned int hwirq = irqd_to_hwirq(d);

	dev_dbg(p->dev, "sense irq = %d, type = %d\n", hwirq, type);

	switch (type & IRQ_TYPE_SENSE_MASK) {
	case IRQ_TYPE_LEVEL_HIGH:
		gpio_rcar_config_interrupt_input_mode(p, hwirq, true, true,
						      false);
		break;
	case IRQ_TYPE_LEVEL_LOW:
		gpio_rcar_config_interrupt_input_mode(p, hwirq, false, true,
						      false);
		break;
	case IRQ_TYPE_EDGE_RISING:
		gpio_rcar_config_interrupt_input_mode(p, hwirq, true, false,
						      false);
		break;
	case IRQ_TYPE_EDGE_FALLING:
		gpio_rcar_config_interrupt_input_mode(p, hwirq, false, false,
						      false);
		break;
	case IRQ_TYPE_EDGE_BOTH:
		if (!p->has_both_edge_trigger)
			return -EINVAL;
		gpio_rcar_config_interrupt_input_mode(p, hwirq, true, false,
						      true);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}