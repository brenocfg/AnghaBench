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
typedef  int /*<<< orphan*/  u32 ;
struct irq_data {int dummy; } ;
struct gpio_chip {int dummy; } ;
struct ftgpio_gpio {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ GPIO_INT_BOTH_EDGE ; 
 scalar_t__ GPIO_INT_LEVEL ; 
 scalar_t__ GPIO_INT_TYPE ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 int /*<<< orphan*/  ftgpio_gpio_ack_irq (struct irq_data*) ; 
 struct ftgpio_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  handle_bad_irq ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_set_handler_locked (struct irq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ftgpio_gpio_set_irq_type(struct irq_data *d, unsigned int type)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct ftgpio_gpio *g = gpiochip_get_data(gc);
	u32 mask = BIT(irqd_to_hwirq(d));
	u32 reg_both, reg_level, reg_type;

	reg_type = readl(g->base + GPIO_INT_TYPE);
	reg_level = readl(g->base + GPIO_INT_LEVEL);
	reg_both = readl(g->base + GPIO_INT_BOTH_EDGE);

	switch (type) {
	case IRQ_TYPE_EDGE_BOTH:
		irq_set_handler_locked(d, handle_edge_irq);
		reg_type &= ~mask;
		reg_both |= mask;
		break;
	case IRQ_TYPE_EDGE_RISING:
		irq_set_handler_locked(d, handle_edge_irq);
		reg_type &= ~mask;
		reg_both &= ~mask;
		reg_level &= ~mask;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		irq_set_handler_locked(d, handle_edge_irq);
		reg_type &= ~mask;
		reg_both &= ~mask;
		reg_level |= mask;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		irq_set_handler_locked(d, handle_level_irq);
		reg_type |= mask;
		reg_level &= ~mask;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		irq_set_handler_locked(d, handle_level_irq);
		reg_type |= mask;
		reg_level |= mask;
		break;
	default:
		irq_set_handler_locked(d, handle_bad_irq);
		return -EINVAL;
	}

	writel(reg_type, g->base + GPIO_INT_TYPE);
	writel(reg_level, g->base + GPIO_INT_LEVEL);
	writel(reg_both, g->base + GPIO_INT_BOTH_EDGE);

	ftgpio_gpio_ack_irq(d);

	return 0;
}