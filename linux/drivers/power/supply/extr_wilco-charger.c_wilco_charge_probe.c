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
struct wilco_ec_device {int dummy; } ;
struct power_supply_config {struct wilco_ec_device* drv_data; } ;
struct power_supply {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (struct power_supply*) ; 
 struct wilco_ec_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct power_supply* devm_power_supply_register (TYPE_1__*,int /*<<< orphan*/ *,struct power_supply_config*) ; 
 int /*<<< orphan*/  wilco_ps_desc ; 

__attribute__((used)) static int wilco_charge_probe(struct platform_device *pdev)
{
	struct wilco_ec_device *ec = dev_get_drvdata(pdev->dev.parent);
	struct power_supply_config psy_cfg = {};
	struct power_supply *psy;

	psy_cfg.drv_data = ec;
	psy = devm_power_supply_register(&pdev->dev, &wilco_ps_desc, &psy_cfg);

	return PTR_ERR_OR_ZERO(psy);
}