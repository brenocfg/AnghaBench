#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_4__ {unsigned int irq_flags; } ;
struct madera {int irq; TYPE_2__* irq_dev; int /*<<< orphan*/  irq_data; int /*<<< orphan*/  regmap; TYPE_1__ pdata; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 unsigned int IRQF_TRIGGER_FALLING ; 
 unsigned int IRQF_TRIGGER_HIGH ; 
 unsigned int IRQF_TRIGGER_LOW ; 
 unsigned int IRQF_TRIGGER_RISING ; 
 unsigned int IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  MADERA_IRQ1_CTRL ; 
 int /*<<< orphan*/  MADERA_IRQ_POL_MASK ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct madera* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct irq_data* irq_get_irq_data (int) ; 
 unsigned int irqd_get_trigger_type (struct irq_data*) ; 
 int /*<<< orphan*/  madera_irq_chip ; 
 int regmap_add_irq_chip (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int madera_irq_probe(struct platform_device *pdev)
{
	struct madera *madera = dev_get_drvdata(pdev->dev.parent);
	struct irq_data *irq_data;
	unsigned int irq_flags = 0;
	int ret;

	dev_dbg(&pdev->dev, "probe\n");

	/*
	 * Read the flags from the interrupt controller if not specified
	 * by pdata
	 */
	irq_flags = madera->pdata.irq_flags;
	if (!irq_flags) {
		irq_data = irq_get_irq_data(madera->irq);
		if (!irq_data) {
			dev_err(&pdev->dev, "Invalid IRQ: %d\n", madera->irq);
			return -EINVAL;
		}

		irq_flags = irqd_get_trigger_type(irq_data);

		/* Codec defaults to trigger low, use this if no flags given */
		if (irq_flags == IRQ_TYPE_NONE)
			irq_flags = IRQF_TRIGGER_LOW;
	}

	if (irq_flags & (IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING)) {
		dev_err(&pdev->dev, "Host interrupt not level-triggered\n");
		return -EINVAL;
	}

	/*
	 * The silicon always starts at active-low, check if we need to
	 * switch to active-high.
	 */
	if (irq_flags & IRQF_TRIGGER_HIGH) {
		ret = regmap_update_bits(madera->regmap, MADERA_IRQ1_CTRL,
					 MADERA_IRQ_POL_MASK, 0);
		if (ret) {
			dev_err(&pdev->dev,
				"Failed to set IRQ polarity: %d\n", ret);
			return ret;
		}
	}

	/*
	 * NOTE: regmap registers this against the OF node of the parent of
	 * the regmap - that is, against the mfd driver
	 */
	ret = regmap_add_irq_chip(madera->regmap, madera->irq, IRQF_ONESHOT, 0,
				  &madera_irq_chip, &madera->irq_data);
	if (ret) {
		dev_err(&pdev->dev, "add_irq_chip failed: %d\n", ret);
		return ret;
	}

	/* Save dev in parent MFD struct so it is accessible to siblings */
	madera->irq_dev = &pdev->dev;

	return 0;
}