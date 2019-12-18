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
struct samsung_pinctrl_drv_data {scalar_t__ virt_base; } ;
struct s3c64xx_eint_gpio_data {int /*<<< orphan*/ * domains; struct samsung_pinctrl_drv_data* drvdata; } ;
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ SERVICE_REG ; 
 unsigned int SVC_GROUP (unsigned int) ; 
 unsigned int SVC_NUM_MASK ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct s3c64xx_eint_gpio_data* irq_desc_get_handler_data (struct irq_desc*) ; 
 unsigned int irq_linear_revmap (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static void s3c64xx_eint_gpio_irq(struct irq_desc *desc)
{
	struct irq_chip *chip = irq_desc_get_chip(desc);
	struct s3c64xx_eint_gpio_data *data = irq_desc_get_handler_data(desc);
	struct samsung_pinctrl_drv_data *drvdata = data->drvdata;

	chained_irq_enter(chip, desc);

	do {
		unsigned int svc;
		unsigned int group;
		unsigned int pin;
		unsigned int virq;

		svc = readl(drvdata->virt_base + SERVICE_REG);
		group = SVC_GROUP(svc);
		pin = svc & SVC_NUM_MASK;

		if (!group)
			break;

		/* Group 1 is used for two pin banks */
		if (group == 1) {
			if (pin < 8)
				group = 0;
			else
				pin -= 8;
		}

		virq = irq_linear_revmap(data->domains[group], pin);
		/*
		 * Something must be really wrong if an unmapped EINT
		 * was unmasked...
		 */
		BUG_ON(!virq);

		generic_handle_irq(virq);
	} while (1);

	chained_irq_exit(chip, desc);
}