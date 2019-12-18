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
struct regulator_dev {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  regmap; struct pcf50633* driver_data; int /*<<< orphan*/  init_data; TYPE_2__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct platform_device {size_t id; TYPE_2__ dev; } ;
struct pcf50633 {TYPE_1__* pdata; int /*<<< orphan*/  regmap; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* regulator_registered ) (struct pcf50633*,size_t) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_get_platdata (TYPE_2__*) ; 
 struct pcf50633* dev_to_pcf50633 (int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_2__*,int /*<<< orphan*/ *,struct regulator_config*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct regulator_dev*) ; 
 int /*<<< orphan*/ * regulators ; 
 int /*<<< orphan*/  stub1 (struct pcf50633*,size_t) ; 

__attribute__((used)) static int pcf50633_regulator_probe(struct platform_device *pdev)
{
	struct regulator_dev *rdev;
	struct pcf50633 *pcf;
	struct regulator_config config = { };

	/* Already set by core driver */
	pcf = dev_to_pcf50633(pdev->dev.parent);

	config.dev = &pdev->dev;
	config.init_data = dev_get_platdata(&pdev->dev);
	config.driver_data = pcf;
	config.regmap = pcf->regmap;

	rdev = devm_regulator_register(&pdev->dev, &regulators[pdev->id],
				       &config);
	if (IS_ERR(rdev))
		return PTR_ERR(rdev);

	platform_set_drvdata(pdev, rdev);

	if (pcf->pdata->regulator_registered)
		pcf->pdata->regulator_registered(pcf, pdev->id);

	return 0;
}