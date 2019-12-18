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
typedef  unsigned int u32 ;
struct samsung_pinctrl_drv_data {scalar_t__ virt_base; } ;
struct s3c64xx_eint0_data {int /*<<< orphan*/ * pins; int /*<<< orphan*/ * domains; struct samsung_pinctrl_drv_data* drvdata; } ;
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ EINT0MASK_REG ; 
 scalar_t__ EINT0PEND_REG ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 int fls (unsigned int) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct s3c64xx_eint0_data* irq_desc_get_handler_data (struct irq_desc*) ; 
 unsigned int irq_linear_revmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static inline void s3c64xx_irq_demux_eint(struct irq_desc *desc, u32 range)
{
	struct irq_chip *chip = irq_desc_get_chip(desc);
	struct s3c64xx_eint0_data *data = irq_desc_get_handler_data(desc);
	struct samsung_pinctrl_drv_data *drvdata = data->drvdata;
	unsigned int pend, mask;

	chained_irq_enter(chip, desc);

	pend = readl(drvdata->virt_base + EINT0PEND_REG);
	mask = readl(drvdata->virt_base + EINT0MASK_REG);

	pend = pend & range & ~mask;
	pend &= range;

	while (pend) {
		unsigned int virq, irq;

		irq = fls(pend) - 1;
		pend &= ~(1 << irq);
		virq = irq_linear_revmap(data->domains[irq], data->pins[irq]);
		/*
		 * Something must be really wrong if an unmapped EINT
		 * was unmasked...
		 */
		BUG_ON(!virq);

		generic_handle_irq(virq);
	}

	chained_irq_exit(chip, desc);
}