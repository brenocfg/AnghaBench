#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {int dummy; } ;
struct regulator_desc {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  regmap; struct bcm590xx_reg* driver_data; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct bcm590xx_reg {TYPE_2__* desc; struct bcm590xx* mfd; } ;
struct bcm590xx_info {char* name; int /*<<< orphan*/  n_linear_ranges; int /*<<< orphan*/  linear_ranges; int /*<<< orphan*/  n_voltages; int /*<<< orphan*/  volt_table; int /*<<< orphan*/  vin_name; } ;
struct bcm590xx {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap_pri; int /*<<< orphan*/  regmap_sec; } ;
struct TYPE_7__ {char* name; int id; int enable_is_inverted; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/  enable_reg; int /*<<< orphan*/  enable_mask; int /*<<< orphan*/  vsel_reg; int /*<<< orphan*/  vsel_mask; int /*<<< orphan*/ * ops; int /*<<< orphan*/  n_linear_ranges; int /*<<< orphan*/  linear_ranges; int /*<<< orphan*/  n_voltages; int /*<<< orphan*/  volt_table; int /*<<< orphan*/  supply_name; void* regulators_node; void* of_match; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM590XX_LDO_VSEL_MASK ; 
 int BCM590XX_NUM_REGS ; 
 int /*<<< orphan*/  BCM590XX_REG_ENABLE ; 
 scalar_t__ BCM590XX_REG_IS_GPLDO (int) ; 
 scalar_t__ BCM590XX_REG_IS_LDO (int) ; 
 scalar_t__ BCM590XX_REG_IS_VBUS (int) ; 
 int /*<<< orphan*/  BCM590XX_SR_VSEL_MASK ; 
 int /*<<< orphan*/  BCM590XX_VBUS_ENABLE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  REGULATOR_VOLTAGE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  bcm590xx_get_enable_register (int) ; 
 int /*<<< orphan*/  bcm590xx_get_vsel_register (int) ; 
 int /*<<< orphan*/  bcm590xx_ops_dcdc ; 
 int /*<<< orphan*/  bcm590xx_ops_ldo ; 
 int /*<<< orphan*/  bcm590xx_ops_vbus ; 
 struct bcm590xx_info* bcm590xx_regs ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct bcm590xx* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 TYPE_2__* devm_kcalloc (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 struct bcm590xx_reg* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_1__*,TYPE_2__*,struct regulator_config*) ; 
 void* of_match_ptr (char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bcm590xx_reg*) ; 

__attribute__((used)) static int bcm590xx_probe(struct platform_device *pdev)
{
	struct bcm590xx *bcm590xx = dev_get_drvdata(pdev->dev.parent);
	struct bcm590xx_reg *pmu;
	struct regulator_config config = { };
	struct bcm590xx_info *info;
	struct regulator_dev *rdev;
	int i;

	pmu = devm_kzalloc(&pdev->dev, sizeof(*pmu), GFP_KERNEL);
	if (!pmu)
		return -ENOMEM;

	pmu->mfd = bcm590xx;

	platform_set_drvdata(pdev, pmu);

	pmu->desc = devm_kcalloc(&pdev->dev,
				 BCM590XX_NUM_REGS,
				 sizeof(struct regulator_desc),
				 GFP_KERNEL);
	if (!pmu->desc)
		return -ENOMEM;

	info = bcm590xx_regs;

	for (i = 0; i < BCM590XX_NUM_REGS; i++, info++) {
		/* Register the regulators */
		pmu->desc[i].name = info->name;
		pmu->desc[i].of_match = of_match_ptr(info->name);
		pmu->desc[i].regulators_node = of_match_ptr("regulators");
		pmu->desc[i].supply_name = info->vin_name;
		pmu->desc[i].id = i;
		pmu->desc[i].volt_table = info->volt_table;
		pmu->desc[i].n_voltages = info->n_voltages;
		pmu->desc[i].linear_ranges = info->linear_ranges;
		pmu->desc[i].n_linear_ranges = info->n_linear_ranges;

		if ((BCM590XX_REG_IS_LDO(i)) || (BCM590XX_REG_IS_GPLDO(i))) {
			pmu->desc[i].ops = &bcm590xx_ops_ldo;
			pmu->desc[i].vsel_mask = BCM590XX_LDO_VSEL_MASK;
		} else if (BCM590XX_REG_IS_VBUS(i))
			pmu->desc[i].ops = &bcm590xx_ops_vbus;
		else {
			pmu->desc[i].ops = &bcm590xx_ops_dcdc;
			pmu->desc[i].vsel_mask = BCM590XX_SR_VSEL_MASK;
		}

		if (BCM590XX_REG_IS_VBUS(i))
			pmu->desc[i].enable_mask = BCM590XX_VBUS_ENABLE;
		else {
			pmu->desc[i].vsel_reg = bcm590xx_get_vsel_register(i);
			pmu->desc[i].enable_is_inverted = true;
			pmu->desc[i].enable_mask = BCM590XX_REG_ENABLE;
		}
		pmu->desc[i].enable_reg = bcm590xx_get_enable_register(i);
		pmu->desc[i].type = REGULATOR_VOLTAGE;
		pmu->desc[i].owner = THIS_MODULE;

		config.dev = bcm590xx->dev;
		config.driver_data = pmu;
		if (BCM590XX_REG_IS_GPLDO(i) || BCM590XX_REG_IS_VBUS(i))
			config.regmap = bcm590xx->regmap_sec;
		else
			config.regmap = bcm590xx->regmap_pri;

		rdev = devm_regulator_register(&pdev->dev, &pmu->desc[i],
					       &config);
		if (IS_ERR(rdev)) {
			dev_err(bcm590xx->dev,
				"failed to register %s regulator\n",
				pdev->name);
			return PTR_ERR(rdev);
		}
	}

	return 0;
}