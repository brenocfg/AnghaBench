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
struct pm_irq_chip {int /*<<< orphan*/  regmap; } ;
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 unsigned int GENMASK (int,int) ; 
 int /*<<< orphan*/  PM8821_SSBI_REG_ADDR_IRQ_MASTER0 ; 
 int /*<<< orphan*/  PM8821_SSBI_REG_ADDR_IRQ_MASTER1 ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct pm_irq_chip* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  pm8821_irq_master_handler (struct pm_irq_chip*,int,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static void pm8821_irq_handler(struct irq_desc *desc)
{
	struct pm_irq_chip *chip = irq_desc_get_handler_data(desc);
	struct irq_chip *irq_chip = irq_desc_get_chip(desc);
	unsigned int master;
	int ret;

	chained_irq_enter(irq_chip, desc);
	ret = regmap_read(chip->regmap,
			  PM8821_SSBI_REG_ADDR_IRQ_MASTER0, &master);
	if (ret) {
		pr_err("Failed to read master 0 ret=%d\n", ret);
		goto done;
	}

	/* bits 1 through 7 marks the first 7 blocks in master 0 */
	if (master & GENMASK(7, 1))
		pm8821_irq_master_handler(chip, 0, master);

	/* bit 0 marks if master 1 contains any bits */
	if (!(master & BIT(0)))
		goto done;

	ret = regmap_read(chip->regmap,
			  PM8821_SSBI_REG_ADDR_IRQ_MASTER1, &master);
	if (ret) {
		pr_err("Failed to read master 1 ret=%d\n", ret);
		goto done;
	}

	pm8821_irq_master_handler(chip, 1, master);

done:
	chained_irq_exit(irq_chip, desc);
}