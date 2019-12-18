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
struct pistachio_gpio_bank {int dummy; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_INPUT_POLARITY ; 
 int /*<<< orphan*/  GPIO_INTERRUPT_EDGE ; 
 int GPIO_INTERRUPT_EDGE_DUAL ; 
 int GPIO_INTERRUPT_EDGE_SINGLE ; 
 int /*<<< orphan*/  GPIO_INTERRUPT_TYPE ; 
 int GPIO_INTERRUPT_TYPE_EDGE ; 
 int GPIO_INTERRUPT_TYPE_LEVEL ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int IRQ_TYPE_LEVEL_MASK ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 int /*<<< orphan*/  gpio_mask_writel (struct pistachio_gpio_bank*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_set_handler_locked (struct irq_data*,int /*<<< orphan*/ ) ; 
 struct pistachio_gpio_bank* irqd_to_bank (struct irq_data*) ; 

__attribute__((used)) static int pistachio_gpio_irq_set_type(struct irq_data *data, unsigned int type)
{
	struct pistachio_gpio_bank *bank = irqd_to_bank(data);

	switch (type & IRQ_TYPE_SENSE_MASK) {
	case IRQ_TYPE_EDGE_RISING:
		gpio_mask_writel(bank, GPIO_INPUT_POLARITY, data->hwirq, 1);
		gpio_mask_writel(bank, GPIO_INTERRUPT_TYPE, data->hwirq,
				 GPIO_INTERRUPT_TYPE_EDGE);
		gpio_mask_writel(bank, GPIO_INTERRUPT_EDGE, data->hwirq,
				 GPIO_INTERRUPT_EDGE_SINGLE);
		break;
	case IRQ_TYPE_EDGE_FALLING:
		gpio_mask_writel(bank, GPIO_INPUT_POLARITY, data->hwirq, 0);
		gpio_mask_writel(bank, GPIO_INTERRUPT_TYPE, data->hwirq,
				 GPIO_INTERRUPT_TYPE_EDGE);
		gpio_mask_writel(bank, GPIO_INTERRUPT_EDGE, data->hwirq,
				 GPIO_INTERRUPT_EDGE_SINGLE);
		break;
	case IRQ_TYPE_EDGE_BOTH:
		gpio_mask_writel(bank, GPIO_INTERRUPT_TYPE, data->hwirq,
				 GPIO_INTERRUPT_TYPE_EDGE);
		gpio_mask_writel(bank, GPIO_INTERRUPT_EDGE, data->hwirq,
				 GPIO_INTERRUPT_EDGE_DUAL);
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		gpio_mask_writel(bank, GPIO_INPUT_POLARITY, data->hwirq, 1);
		gpio_mask_writel(bank, GPIO_INTERRUPT_TYPE, data->hwirq,
				 GPIO_INTERRUPT_TYPE_LEVEL);
		break;
	case IRQ_TYPE_LEVEL_LOW:
		gpio_mask_writel(bank, GPIO_INPUT_POLARITY, data->hwirq, 0);
		gpio_mask_writel(bank, GPIO_INTERRUPT_TYPE, data->hwirq,
				 GPIO_INTERRUPT_TYPE_LEVEL);
		break;
	default:
		return -EINVAL;
	}

	if (type & IRQ_TYPE_LEVEL_MASK)
		irq_set_handler_locked(data, handle_level_irq);
	else
		irq_set_handler_locked(data, handle_edge_irq);

	return 0;
}