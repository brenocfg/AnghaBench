#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rk808_regulator_data {int dummy; } ;
struct rk808 {int variant; int /*<<< orphan*/  regmap; struct i2c_client* i2c; } ;
struct regulator_dev {int dummy; } ;
struct regulator_desc {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  regmap; struct rk808_regulator_data* driver_data; int /*<<< orphan*/ * dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
#define  RK805_ID 132 
 int RK805_NUM_REGULATORS ; 
#define  RK808_ID 131 
 int RK808_NUM_REGULATORS ; 
#define  RK809_ID 130 
 int RK809_NUM_REGULATORS ; 
#define  RK817_ID 129 
 int RK817_NUM_REGULATORS ; 
#define  RK818_ID 128 
 int RK818_NUM_REGULATORS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct rk808* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct rk808_regulator_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_1__*,struct regulator_desc const*,struct regulator_config*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rk808_regulator_data*) ; 
 struct regulator_desc* rk805_reg ; 
 struct regulator_desc* rk808_reg ; 
 int rk808_regulator_dt_parse_pdata (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rk808_regulator_data*) ; 
 struct regulator_desc* rk809_reg ; 
 struct regulator_desc* rk817_reg ; 
 struct regulator_desc* rk818_reg ; 

__attribute__((used)) static int rk808_regulator_probe(struct platform_device *pdev)
{
	struct rk808 *rk808 = dev_get_drvdata(pdev->dev.parent);
	struct i2c_client *client = rk808->i2c;
	struct regulator_config config = {};
	struct regulator_dev *rk808_rdev;
	struct rk808_regulator_data *pdata;
	const struct regulator_desc *regulators;
	int ret, i, nregulators;

	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	ret = rk808_regulator_dt_parse_pdata(&pdev->dev, &client->dev,
					     rk808->regmap, pdata);
	if (ret < 0)
		return ret;

	platform_set_drvdata(pdev, pdata);

	switch (rk808->variant) {
	case RK805_ID:
		regulators = rk805_reg;
		nregulators = RK805_NUM_REGULATORS;
		break;
	case RK808_ID:
		regulators = rk808_reg;
		nregulators = RK808_NUM_REGULATORS;
		break;
	case RK809_ID:
		regulators = rk809_reg;
		nregulators = RK809_NUM_REGULATORS;
		break;
	case RK817_ID:
		regulators = rk817_reg;
		nregulators = RK817_NUM_REGULATORS;
		break;
	case RK818_ID:
		regulators = rk818_reg;
		nregulators = RK818_NUM_REGULATORS;
		break;
	default:
		dev_err(&client->dev, "unsupported RK8XX ID %lu\n",
			rk808->variant);
		return -EINVAL;
	}

	config.dev = &client->dev;
	config.driver_data = pdata;
	config.regmap = rk808->regmap;

	/* Instantiate the regulators */
	for (i = 0; i < nregulators; i++) {
		rk808_rdev = devm_regulator_register(&pdev->dev,
						     &regulators[i], &config);
		if (IS_ERR(rk808_rdev)) {
			dev_err(&client->dev,
				"failed to register %d regulator\n", i);
			return PTR_ERR(rk808_rdev);
		}
	}

	return 0;
}