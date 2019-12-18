#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ti_lmu {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct lm36274 {int /*<<< orphan*/  led_dev; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; struct platform_device* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct ti_lmu* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct lm36274*) ; 
 struct lm36274* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_led_classdev_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int lm36274_init (struct lm36274*) ; 
 int lm36274_parse_dt (struct lm36274*) ; 

__attribute__((used)) static int lm36274_probe(struct platform_device *pdev)
{
	struct ti_lmu *lmu = dev_get_drvdata(pdev->dev.parent);
	struct lm36274 *lm36274_data;
	int ret;

	lm36274_data = devm_kzalloc(&pdev->dev, sizeof(*lm36274_data),
				    GFP_KERNEL);
	if (!lm36274_data)
		return -ENOMEM;

	lm36274_data->pdev = pdev;
	lm36274_data->dev = lmu->dev;
	lm36274_data->regmap = lmu->regmap;
	dev_set_drvdata(&pdev->dev, lm36274_data);

	ret = lm36274_parse_dt(lm36274_data);
	if (ret) {
		dev_err(lm36274_data->dev, "Failed to parse DT node\n");
		return ret;
	}

	ret = lm36274_init(lm36274_data);
	if (ret) {
		dev_err(lm36274_data->dev, "Failed to init the device\n");
		return ret;
	}

	return devm_led_classdev_register(lm36274_data->dev,
					 &lm36274_data->led_dev);
}