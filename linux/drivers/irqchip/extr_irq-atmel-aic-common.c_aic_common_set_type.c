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
struct irq_data {int mask; } ;
struct irq_chip_generic {struct aic_chip_data* private; } ;
struct aic_chip_data {int ext_irqs; } ;

/* Variables and functions */
 unsigned int AT91_AIC_SRCTYPE ; 
 unsigned int AT91_AIC_SRCTYPE_FALLING ; 
 unsigned int AT91_AIC_SRCTYPE_HIGH ; 
 unsigned int AT91_AIC_SRCTYPE_LOW ; 
 unsigned int AT91_AIC_SRCTYPE_RISING ; 
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 

int aic_common_set_type(struct irq_data *d, unsigned type, unsigned *val)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	struct aic_chip_data *aic = gc->private;
	unsigned aic_type;

	switch (type) {
	case IRQ_TYPE_LEVEL_HIGH:
		aic_type = AT91_AIC_SRCTYPE_HIGH;
		break;
	case IRQ_TYPE_EDGE_RISING:
		aic_type = AT91_AIC_SRCTYPE_RISING;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		if (!(d->mask & aic->ext_irqs))
			return -EINVAL;

		aic_type = AT91_AIC_SRCTYPE_LOW;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		if (!(d->mask & aic->ext_irqs))
			return -EINVAL;

		aic_type = AT91_AIC_SRCTYPE_FALLING;
		break;
	default:
		return -EINVAL;
	}

	*val &= ~AT91_AIC_SRCTYPE;
	*val |= aic_type;

	return 0;
}