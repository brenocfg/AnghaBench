#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct regmap {int dummy; } ;
struct pm_irq_data {int /*<<< orphan*/ * irq_handler; void* num_irqs; } ;
struct pm_irq_chip {int /*<<< orphan*/  irqdomain; int /*<<< orphan*/  pm_irq_lock; struct pm_irq_data const* pm_irq_data; void* num_blocks; void* num_masters; struct regmap* regmap; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 unsigned int BITS_PER_BYTE ; 
 void* DIV_ROUND_UP (void*,int) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  REG_HWREV ; 
 int /*<<< orphan*/  REG_HWREV_2 ; 
 int /*<<< orphan*/  config ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct pm_irq_chip* devm_kzalloc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct regmap* devm_regmap_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_domain_add_linear (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,struct pm_irq_chip*) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int,int /*<<< orphan*/ *,struct pm_irq_chip*) ; 
 int /*<<< orphan*/  irq_set_irq_wake (int,int) ; 
 struct pm_irq_data* of_device_get_match_data (TYPE_1__*) ; 
 int of_platform_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pm_irq_chip*) ; 
 int /*<<< orphan*/  pm8xxx_irq_domain_ops ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssbi_regmap_config ; 
 int /*<<< orphan*/  struct_size (struct pm_irq_chip*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int pm8xxx_probe(struct platform_device *pdev)
{
	const struct pm_irq_data *data;
	struct regmap *regmap;
	int irq, rc;
	unsigned int val;
	u32 rev;
	struct pm_irq_chip *chip;

	data = of_device_get_match_data(&pdev->dev);
	if (!data) {
		dev_err(&pdev->dev, "No matching driver data found\n");
		return -EINVAL;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	regmap = devm_regmap_init(&pdev->dev, NULL, pdev->dev.parent,
				  &ssbi_regmap_config);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	/* Read PMIC chip revision */
	rc = regmap_read(regmap, REG_HWREV, &val);
	if (rc) {
		pr_err("Failed to read hw rev reg %d:rc=%d\n", REG_HWREV, rc);
		return rc;
	}
	pr_info("PMIC revision 1: %02X\n", val);
	rev = val;

	/* Read PMIC chip revision 2 */
	rc = regmap_read(regmap, REG_HWREV_2, &val);
	if (rc) {
		pr_err("Failed to read hw rev 2 reg %d:rc=%d\n",
			REG_HWREV_2, rc);
		return rc;
	}
	pr_info("PMIC revision 2: %02X\n", val);
	rev |= val << BITS_PER_BYTE;

	chip = devm_kzalloc(&pdev->dev,
			    struct_size(chip, config, data->num_irqs),
			    GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	platform_set_drvdata(pdev, chip);
	chip->regmap = regmap;
	chip->num_blocks = DIV_ROUND_UP(data->num_irqs, 8);
	chip->num_masters = DIV_ROUND_UP(chip->num_blocks, 8);
	chip->pm_irq_data = data;
	spin_lock_init(&chip->pm_irq_lock);

	chip->irqdomain = irq_domain_add_linear(pdev->dev.of_node,
						data->num_irqs,
						&pm8xxx_irq_domain_ops,
						chip);
	if (!chip->irqdomain)
		return -ENODEV;

	irq_set_chained_handler_and_data(irq, data->irq_handler, chip);
	irq_set_irq_wake(irq, 1);

	rc = of_platform_populate(pdev->dev.of_node, NULL, NULL, &pdev->dev);
	if (rc) {
		irq_set_chained_handler_and_data(irq, NULL, NULL);
		irq_domain_remove(chip->irqdomain);
	}

	return rc;
}