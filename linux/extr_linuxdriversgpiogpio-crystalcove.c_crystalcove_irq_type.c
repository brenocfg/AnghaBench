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
struct irq_data {scalar_t__ hwirq; } ;
struct crystalcove_gpio {int /*<<< orphan*/  update; int /*<<< orphan*/  intcnt_value; } ;

/* Variables and functions */
 scalar_t__ CRYSTALCOVE_GPIO_NUM ; 
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
 struct crystalcove_gpio* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static int crystalcove_irq_type(struct irq_data *data, unsigned type)
{
	struct crystalcove_gpio *cg =
		gpiochip_get_data(irq_data_get_irq_chip_data(data));

	if (data->hwirq >= CRYSTALCOVE_GPIO_NUM)
		return 0;

	switch (type) {
	case IRQ_TYPE_NONE:
		cg->intcnt_value = CTLI_INTCNT_DIS;
		break;
	case IRQ_TYPE_EDGE_BOTH:
		cg->intcnt_value = CTLI_INTCNT_BE;
		break;
	case IRQ_TYPE_EDGE_RISING:
		cg->intcnt_value = CTLI_INTCNT_PE;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		cg->intcnt_value = CTLI_INTCNT_NE;
		break;
	default:
		return -EINVAL;
	}

	cg->update |= UPDATE_IRQ_TYPE;

	return 0;
}