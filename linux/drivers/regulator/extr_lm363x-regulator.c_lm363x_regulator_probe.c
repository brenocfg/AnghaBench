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
struct ti_lmu {struct regmap* regmap; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {struct regulator_dev* ena_gpiod; struct regmap* regmap; struct device* dev; } ;
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {int id; struct device dev; } ;
typedef  struct regulator_dev gpio_desc ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 struct ti_lmu* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (struct device*,int /*<<< orphan*/ *,struct regulator_config*) ; 
 int /*<<< orphan*/  gpiod_put (struct regulator_dev*) ; 
 int /*<<< orphan*/ * lm363x_regulator_desc ; 
 struct regulator_dev* lm363x_regulator_of_get_enable_gpio (struct device*,int) ; 
 int lm363x_regulator_set_ext_en (struct regmap*,int) ; 

__attribute__((used)) static int lm363x_regulator_probe(struct platform_device *pdev)
{
	struct ti_lmu *lmu = dev_get_drvdata(pdev->dev.parent);
	struct regmap *regmap = lmu->regmap;
	struct regulator_config cfg = { };
	struct regulator_dev *rdev;
	struct device *dev = &pdev->dev;
	int id = pdev->id;
	struct gpio_desc *gpiod;
	int ret;

	cfg.dev = dev;
	cfg.regmap = regmap;

	/*
	 * LM3632 LDOs can be controlled by external pin.
	 * Register update is required if the pin is used.
	 */
	gpiod = lm363x_regulator_of_get_enable_gpio(dev, id);
	if (IS_ERR(gpiod))
		return PTR_ERR(gpiod);

	if (gpiod) {
		cfg.ena_gpiod = gpiod;
		ret = lm363x_regulator_set_ext_en(regmap, id);
		if (ret) {
			gpiod_put(gpiod);
			dev_err(dev, "External pin err: %d\n", ret);
			return ret;
		}
	}

	rdev = devm_regulator_register(dev, &lm363x_regulator_desc[id], &cfg);
	if (IS_ERR(rdev)) {
		ret = PTR_ERR(rdev);
		dev_err(dev, "[%d] regulator register err: %d\n", id, ret);
		return ret;
	}

	return 0;
}