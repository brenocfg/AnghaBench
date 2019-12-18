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
typedef  int u8 ;
struct pm_irq_chip {int /*<<< orphan*/  regmap; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int PM8821_BLOCKS_PER_MASTER ; 
 int /*<<< orphan*/  PM8821_SSBI_ADDR_IRQ_CLEAR (int,int) ; 
 int /*<<< orphan*/  PM8821_SSBI_ADDR_IRQ_MASK (int,int) ; 
 struct pm_irq_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 unsigned int irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pm8821_irq_mask_ack(struct irq_data *d)
{
	struct pm_irq_chip *chip = irq_data_get_irq_chip_data(d);
	unsigned int pmirq = irqd_to_hwirq(d);
	u8 block, master;
	int irq_bit, rc;

	block = pmirq / 8;
	master = block / PM8821_BLOCKS_PER_MASTER;
	irq_bit = pmirq % 8;
	block %= PM8821_BLOCKS_PER_MASTER;

	rc = regmap_update_bits(chip->regmap,
				PM8821_SSBI_ADDR_IRQ_MASK(master, block),
				BIT(irq_bit), BIT(irq_bit));
	if (rc) {
		pr_err("Failed to mask IRQ:%d rc=%d\n", pmirq, rc);
		return;
	}

	rc = regmap_update_bits(chip->regmap,
				PM8821_SSBI_ADDR_IRQ_CLEAR(master, block),
				BIT(irq_bit), BIT(irq_bit));
	if (rc)
		pr_err("Failed to CLEAR IRQ:%d rc=%d\n", pmirq, rc);
}