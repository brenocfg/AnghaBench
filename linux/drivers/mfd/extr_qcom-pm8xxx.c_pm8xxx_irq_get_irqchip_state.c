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
typedef  unsigned int u8 ;
struct pm_irq_chip {int /*<<< orphan*/  pm_irq_lock; int /*<<< orphan*/  regmap; } ;
struct irq_data {int dummy; } ;
typedef  enum irqchip_irq_state { ____Placeholder_irqchip_irq_state } irqchip_irq_state ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int EINVAL ; 
 int IRQCHIP_STATE_LINE_LEVEL ; 
 int /*<<< orphan*/  SSBI_REG_ADDR_IRQ_BLK_SEL ; 
 int /*<<< orphan*/  SSBI_REG_ADDR_IRQ_RT_STATUS ; 
 struct pm_irq_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 unsigned int irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pm8xxx_irq_get_irqchip_state(struct irq_data *d,
					enum irqchip_irq_state which,
					bool *state)
{
	struct pm_irq_chip *chip = irq_data_get_irq_chip_data(d);
	unsigned int pmirq = irqd_to_hwirq(d);
	unsigned int bits;
	int irq_bit;
	u8 block;
	int rc;

	if (which != IRQCHIP_STATE_LINE_LEVEL)
		return -EINVAL;

	block = pmirq / 8;
	irq_bit = pmirq % 8;

	spin_lock(&chip->pm_irq_lock);
	rc = regmap_write(chip->regmap, SSBI_REG_ADDR_IRQ_BLK_SEL, block);
	if (rc) {
		pr_err("Failed Selecting Block %d rc=%d\n", block, rc);
		goto bail;
	}

	rc = regmap_read(chip->regmap, SSBI_REG_ADDR_IRQ_RT_STATUS, &bits);
	if (rc) {
		pr_err("Failed Reading Status rc=%d\n", rc);
		goto bail;
	}

	*state = !!(bits & BIT(irq_bit));
bail:
	spin_unlock(&chip->pm_irq_lock);

	return rc;
}