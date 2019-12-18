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
struct wcove_gpio {int /*<<< orphan*/  update; int /*<<< orphan*/  intcnt; } ;
struct irq_data {scalar_t__ hwirq; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLI_INTCNT_BE ; 
 int /*<<< orphan*/  CTLI_INTCNT_DIS ; 
 int /*<<< orphan*/  CTLI_INTCNT_NE ; 
 int /*<<< orphan*/  CTLI_INTCNT_PE ; 
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_BOTH 131 
#define  IRQ_TYPE_EDGE_FALLING 130 
#define  IRQ_TYPE_EDGE_RISING 129 
#define  IRQ_TYPE_NONE 128 
 int /*<<< orphan*/  UPDATE_IRQ_TYPE ; 
 scalar_t__ WCOVE_GPIO_NUM ; 
 struct wcove_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static int wcove_irq_type(struct irq_data *data, unsigned int type)
{
	struct gpio_chip *chip = irq_data_get_irq_chip_data(data);
	struct wcove_gpio *wg = gpiochip_get_data(chip);

	if (data->hwirq >= WCOVE_GPIO_NUM)
		return 0;

	switch (type) {
	case IRQ_TYPE_NONE:
		wg->intcnt = CTLI_INTCNT_DIS;
		break;
	case IRQ_TYPE_EDGE_BOTH:
		wg->intcnt = CTLI_INTCNT_BE;
		break;
	case IRQ_TYPE_EDGE_RISING:
		wg->intcnt = CTLI_INTCNT_PE;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		wg->intcnt = CTLI_INTCNT_NE;
		break;
	default:
		return -EINVAL;
	}

	wg->update |= UPDATE_IRQ_TYPE;

	return 0;
}