#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {int dummy; } ;
struct regulator_config {struct max77802_regulator_prv* driver_data; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct max77802_regulator_prv {int* opmode; } ;
struct max77686_dev {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int id; int /*<<< orphan*/  enable_reg; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int MAX77802_OPMODE_MASK ; 
 void* MAX77802_OPMODE_NORMAL ; 
 int MAX77802_REG_MAX ; 
 int MAX77802_STATUS_OFF ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int,int) ; 
 struct max77686_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*,int) ; 
 struct max77802_regulator_prv* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_2__*,TYPE_1__*,struct regulator_config*) ; 
 int max77802_get_opmode_shift (int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct max77802_regulator_prv*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* regulators ; 

__attribute__((used)) static int max77802_pmic_probe(struct platform_device *pdev)
{
	struct max77686_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	struct max77802_regulator_prv *max77802;
	int i, val;
	struct regulator_config config = { };

	max77802 = devm_kzalloc(&pdev->dev,
				sizeof(struct max77802_regulator_prv),
				GFP_KERNEL);
	if (!max77802)
		return -ENOMEM;

	config.dev = iodev->dev;
	config.regmap = iodev->regmap;
	config.driver_data = max77802;
	platform_set_drvdata(pdev, max77802);

	for (i = 0; i < MAX77802_REG_MAX; i++) {
		struct regulator_dev *rdev;
		int id = regulators[i].id;
		int shift = max77802_get_opmode_shift(id);
		int ret;

		ret = regmap_read(iodev->regmap, regulators[i].enable_reg, &val);
		if (ret < 0) {
			dev_warn(&pdev->dev,
				"cannot read current mode for %d\n", i);
			val = MAX77802_OPMODE_NORMAL;
		} else {
			val = val >> shift & MAX77802_OPMODE_MASK;
		}

		/*
		 * If the regulator is disabled and the system warm rebooted,
		 * the hardware reports OFF as the regulator operating mode.
		 * Default to operating mode NORMAL in that case.
		 */
		if (val == MAX77802_STATUS_OFF)
			max77802->opmode[id] = MAX77802_OPMODE_NORMAL;
		else
			max77802->opmode[id] = val;

		rdev = devm_regulator_register(&pdev->dev,
					       &regulators[i], &config);
		if (IS_ERR(rdev)) {
			ret = PTR_ERR(rdev);
			dev_err(&pdev->dev,
				"regulator init failed for %d: %d\n", i, ret);
			return ret;
		}
	}

	return 0;
}