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
struct pm_irq_chip {int num_masters; int /*<<< orphan*/  regmap; } ;
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSBI_REG_ADDR_IRQ_ROOT ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct pm_irq_chip* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  pm8xxx_irq_master_handler (struct pm_irq_chip*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static void pm8xxx_irq_handler(struct irq_desc *desc)
{
	struct pm_irq_chip *chip = irq_desc_get_handler_data(desc);
	struct irq_chip *irq_chip = irq_desc_get_chip(desc);
	unsigned int root;
	int	i, ret, masters = 0;

	chained_irq_enter(irq_chip, desc);

	ret = regmap_read(chip->regmap, SSBI_REG_ADDR_IRQ_ROOT, &root);
	if (ret) {
		pr_err("Can't read root status ret=%d\n", ret);
		return;
	}

	/* on pm8xxx series masters start from bit 1 of the root */
	masters = root >> 1;

	/* Read allowed masters for blocks. */
	for (i = 0; i < chip->num_masters; i++)
		if (masters & (1 << i))
			pm8xxx_irq_master_handler(chip, i);

	chained_irq_exit(irq_chip, desc);
}