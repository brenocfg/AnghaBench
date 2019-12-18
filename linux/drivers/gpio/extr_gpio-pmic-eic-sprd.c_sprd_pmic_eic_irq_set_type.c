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
struct sprd_pmic_eic {int* reg; } ;
struct irq_data {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 size_t REG_IEV ; 
 struct sprd_pmic_eic* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static int sprd_pmic_eic_irq_set_type(struct irq_data *data,
				      unsigned int flow_type)
{
	struct gpio_chip *chip = irq_data_get_irq_chip_data(data);
	struct sprd_pmic_eic *pmic_eic = gpiochip_get_data(chip);

	switch (flow_type) {
	case IRQ_TYPE_LEVEL_HIGH:
		pmic_eic->reg[REG_IEV] = 1;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		pmic_eic->reg[REG_IEV] = 0;
		break;
	case IRQ_TYPE_EDGE_RISING:
	case IRQ_TYPE_EDGE_FALLING:
	case IRQ_TYPE_EDGE_BOTH:
		/*
		 * Will set the trigger level according to current EIC level
		 * in irq_bus_sync_unlock() interface, so here nothing to do.
		 */
		break;
	default:
		return -ENOTSUPP;
	}

	return 0;
}