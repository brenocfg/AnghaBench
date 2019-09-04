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
struct regmap_irq_chip_data {int dummy; } ;
struct regmap_irq_chip {int /*<<< orphan*/  name; } ;
struct intel_soc_pmic {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 
 int devm_regmap_add_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct regmap_irq_chip const*,struct regmap_irq_chip_data**) ; 
 int regmap_irq_get_virq (struct regmap_irq_chip_data*,int) ; 

__attribute__((used)) static int bxtwc_add_chained_irq_chip(struct intel_soc_pmic *pmic,
				struct regmap_irq_chip_data *pdata,
				int pirq, int irq_flags,
				const struct regmap_irq_chip *chip,
				struct regmap_irq_chip_data **data)
{
	int irq;

	irq = regmap_irq_get_virq(pdata, pirq);
	if (irq < 0) {
		dev_err(pmic->dev,
			"Failed to get parent vIRQ(%d) for chip %s, ret:%d\n",
			pirq, chip->name, irq);
		return irq;
	}

	return devm_regmap_add_irq_chip(pmic->dev, pmic->regmap, irq, irq_flags,
					0, chip, data);
}