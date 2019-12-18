#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct power_supply_config {int /*<<< orphan*/  of_node; struct bd70528_psy* drv_data; } ;
struct TYPE_5__ {TYPE_3__* parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct bd70528_psy {int /*<<< orphan*/  psy; TYPE_1__* dev; int /*<<< orphan*/  regmap; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bd70528_charger_desc ; 
 int bd70528_get_irqs (struct platform_device*,struct bd70528_psy*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_get_regmap (TYPE_3__*,int /*<<< orphan*/ *) ; 
 struct bd70528_psy* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_power_supply_register (TYPE_1__*,int /*<<< orphan*/ *,struct power_supply_config*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bd70528_psy*) ; 

__attribute__((used)) static int bd70528_power_probe(struct platform_device *pdev)
{
	struct bd70528_psy *bdpsy;
	struct power_supply_config cfg = {};

	bdpsy = devm_kzalloc(&pdev->dev, sizeof(*bdpsy), GFP_KERNEL);
	if (!bdpsy)
		return -ENOMEM;

	bdpsy->regmap = dev_get_regmap(pdev->dev.parent, NULL);
	if (!bdpsy->regmap) {
		dev_err(&pdev->dev, "No regmap found for chip\n");
		return -EINVAL;
	}
	bdpsy->dev = &pdev->dev;

	platform_set_drvdata(pdev, bdpsy);
	cfg.drv_data = bdpsy;
	cfg.of_node = pdev->dev.parent->of_node;

	bdpsy->psy = devm_power_supply_register(&pdev->dev,
						&bd70528_charger_desc, &cfg);
	if (IS_ERR(bdpsy->psy)) {
		dev_err(&pdev->dev, "failed: power supply register\n");
		return PTR_ERR(bdpsy->psy);
	}

	return bd70528_get_irqs(pdev, bdpsy);
}