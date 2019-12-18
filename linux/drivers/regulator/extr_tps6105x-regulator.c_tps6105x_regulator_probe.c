#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tps6105x_platform_data {scalar_t__ mode; int /*<<< orphan*/  regulator_data; } ;
struct tps6105x {TYPE_1__* client; int /*<<< orphan*/  regulator; int /*<<< orphan*/  regmap; struct tps6105x_platform_data* pdata; } ;
struct regulator_config {int /*<<< orphan*/  regmap; struct tps6105x* driver_data; int /*<<< orphan*/  init_data; int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ TPS6105X_MODE_VOLTAGE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct tps6105x* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_regulator_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct regulator_config*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tps6105x*) ; 
 int /*<<< orphan*/  tps6105x_regulator_desc ; 

__attribute__((used)) static int tps6105x_regulator_probe(struct platform_device *pdev)
{
	struct tps6105x *tps6105x = dev_get_platdata(&pdev->dev);
	struct tps6105x_platform_data *pdata = tps6105x->pdata;
	struct regulator_config config = { };
	int ret;

	/* This instance is not set for regulator mode so bail out */
	if (pdata->mode != TPS6105X_MODE_VOLTAGE) {
		dev_info(&pdev->dev,
			"chip not in voltage mode mode, exit probe\n");
		return 0;
	}

	config.dev = &tps6105x->client->dev;
	config.init_data = pdata->regulator_data;
	config.driver_data = tps6105x;
	config.regmap = tps6105x->regmap;

	/* Register regulator with framework */
	tps6105x->regulator = devm_regulator_register(&pdev->dev,
						      &tps6105x_regulator_desc,
						      &config);
	if (IS_ERR(tps6105x->regulator)) {
		ret = PTR_ERR(tps6105x->regulator);
		dev_err(&tps6105x->client->dev,
			"failed to register regulator\n");
		return ret;
	}
	platform_set_drvdata(pdev, tps6105x);

	return 0;
}