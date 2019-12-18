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
struct pm_irq_chip {int /*<<< orphan*/  pm_irq_lock; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int PM_IRQF_WRITE ; 
 int /*<<< orphan*/  SSBI_REG_ADDR_IRQ_BLK_SEL ; 
 int /*<<< orphan*/  SSBI_REG_ADDR_IRQ_CONFIG ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pm8xxx_config_irq(struct pm_irq_chip *chip, unsigned int bp, unsigned int cp)
{
	int	rc;

	spin_lock(&chip->pm_irq_lock);
	rc = regmap_write(chip->regmap, SSBI_REG_ADDR_IRQ_BLK_SEL, bp);
	if (rc) {
		pr_err("Failed Selecting Block %d rc=%d\n", bp, rc);
		goto bail;
	}

	cp |= PM_IRQF_WRITE;
	rc = regmap_write(chip->regmap, SSBI_REG_ADDR_IRQ_CONFIG, cp);
	if (rc)
		pr_err("Failed Configuring IRQ rc=%d\n", rc);
bail:
	spin_unlock(&chip->pm_irq_lock);
	return rc;
}