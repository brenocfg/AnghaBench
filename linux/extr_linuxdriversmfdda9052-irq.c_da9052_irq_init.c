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
struct da9052 {int /*<<< orphan*/  irq_data; int /*<<< orphan*/  chip_irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_IRQ_ADC_EOM ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 int /*<<< orphan*/  da9052_auxadc_irq ; 
 int /*<<< orphan*/  da9052_regmap_irq_chip ; 
 int da9052_request_irq (struct da9052*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct da9052*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  enable_irq_wake (int /*<<< orphan*/ ) ; 
 int regmap_add_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int da9052_irq_init(struct da9052 *da9052)
{
	int ret;

	ret = regmap_add_irq_chip(da9052->regmap, da9052->chip_irq,
				  IRQF_TRIGGER_LOW | IRQF_ONESHOT,
				  -1, &da9052_regmap_irq_chip,
				  &da9052->irq_data);
	if (ret < 0) {
		dev_err(da9052->dev, "regmap_add_irq_chip failed: %d\n", ret);
		goto regmap_err;
	}

	enable_irq_wake(da9052->chip_irq);

	ret = da9052_request_irq(da9052, DA9052_IRQ_ADC_EOM, "adc-irq",
			    da9052_auxadc_irq, da9052);

	if (ret != 0) {
		dev_err(da9052->dev, "DA9052_IRQ_ADC_EOM failed: %d\n", ret);
		goto request_irq_err;
	}

	return 0;

request_irq_err:
	regmap_del_irq_chip(da9052->chip_irq, da9052->irq_data);
regmap_err:
	return ret;

}