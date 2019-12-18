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
struct regulator_config {int /*<<< orphan*/  regmap; struct lp8788_buck* driver_data; int /*<<< orphan*/ * init_data; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {int id; TYPE_2__ dev; } ;
struct lp8788_buck {struct regulator_dev* regulator; struct lp8788* lp; } ;
struct lp8788 {int /*<<< orphan*/  regmap; TYPE_1__* pdata; } ;
struct TYPE_5__ {int /*<<< orphan*/ ** buck_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int LP8788_NUM_BUCKS ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int,int) ; 
 struct lp8788* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct lp8788_buck* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_2__*,int /*<<< orphan*/ *,struct regulator_config*) ; 
 int /*<<< orphan*/ * lp8788_buck_desc ; 
 int lp8788_init_dvs (struct platform_device*,struct lp8788_buck*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lp8788_buck*) ; 

__attribute__((used)) static int lp8788_buck_probe(struct platform_device *pdev)
{
	struct lp8788 *lp = dev_get_drvdata(pdev->dev.parent);
	int id = pdev->id;
	struct lp8788_buck *buck;
	struct regulator_config cfg = { };
	struct regulator_dev *rdev;
	int ret;

	if (id >= LP8788_NUM_BUCKS)
		return -EINVAL;

	buck = devm_kzalloc(&pdev->dev, sizeof(struct lp8788_buck), GFP_KERNEL);
	if (!buck)
		return -ENOMEM;

	buck->lp = lp;

	ret = lp8788_init_dvs(pdev, buck, id);
	if (ret)
		return ret;

	cfg.dev = pdev->dev.parent;
	cfg.init_data = lp->pdata ? lp->pdata->buck_data[id] : NULL;
	cfg.driver_data = buck;
	cfg.regmap = lp->regmap;

	rdev = devm_regulator_register(&pdev->dev, &lp8788_buck_desc[id], &cfg);
	if (IS_ERR(rdev)) {
		ret = PTR_ERR(rdev);
		dev_err(&pdev->dev, "BUCK%d regulator register err = %d\n",
				id + 1, ret);
		return ret;
	}

	buck->regulator = rdev;
	platform_set_drvdata(pdev, buck);

	return 0;
}