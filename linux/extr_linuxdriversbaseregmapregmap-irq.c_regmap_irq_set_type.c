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
struct regmap_irq_chip_data {int* type_buf; struct regmap* map; } ;
struct regmap_irq {int type_reg_offset; int type_rising_mask; int type_falling_mask; } ;
struct regmap {int reg_stride; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_BOTH 130 
#define  IRQ_TYPE_EDGE_FALLING 129 
#define  IRQ_TYPE_EDGE_RISING 128 
 struct regmap_irq_chip_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct regmap_irq* irq_to_regmap_irq (struct regmap_irq_chip_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int regmap_irq_set_type(struct irq_data *data, unsigned int type)
{
	struct regmap_irq_chip_data *d = irq_data_get_irq_chip_data(data);
	struct regmap *map = d->map;
	const struct regmap_irq *irq_data = irq_to_regmap_irq(d, data->hwirq);
	int reg = irq_data->type_reg_offset / map->reg_stride;

	if (!(irq_data->type_rising_mask | irq_data->type_falling_mask))
		return 0;

	d->type_buf[reg] &= ~(irq_data->type_falling_mask |
					irq_data->type_rising_mask);
	switch (type) {
	case IRQ_TYPE_EDGE_FALLING:
		d->type_buf[reg] |= irq_data->type_falling_mask;
		break;

	case IRQ_TYPE_EDGE_RISING:
		d->type_buf[reg] |= irq_data->type_rising_mask;
		break;

	case IRQ_TYPE_EDGE_BOTH:
		d->type_buf[reg] |= (irq_data->type_falling_mask |
					irq_data->type_rising_mask);
		break;

	default:
		return -EINVAL;
	}
	return 0;
}