#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  regmap; struct hi6421_regulator_info* driver_data; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct hi6421_regulator_pdata {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct hi6421_regulator_info {TYPE_2__ desc; } ;
struct hi6421_pmic {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct hi6421_regulator_info*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 struct hi6421_pmic* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct hi6421_regulator_pdata* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_1__*,TYPE_2__*,struct regulator_config*) ; 
 struct hi6421_regulator_info* hi6421_regulator_info ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct hi6421_regulator_pdata*) ; 

__attribute__((used)) static int hi6421_regulator_probe(struct platform_device *pdev)
{
	struct hi6421_pmic *pmic = dev_get_drvdata(pdev->dev.parent);
	struct hi6421_regulator_pdata *pdata;
	struct hi6421_regulator_info *info;
	struct regulator_config config = { };
	struct regulator_dev *rdev;
	int i;

	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;
	mutex_init(&pdata->lock);
	platform_set_drvdata(pdev, pdata);

	for (i = 0; i < ARRAY_SIZE(hi6421_regulator_info); i++) {
		/* assign per-regulator data */
		info = &hi6421_regulator_info[i];

		config.dev = pdev->dev.parent;
		config.driver_data = info;
		config.regmap = pmic->regmap;

		rdev = devm_regulator_register(&pdev->dev, &info->desc,
					       &config);
		if (IS_ERR(rdev)) {
			dev_err(&pdev->dev, "failed to register regulator %s\n",
				info->desc.name);
			return PTR_ERR(rdev);
		}
	}

	return 0;
}