#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct power_supply_config {int /*<<< orphan*/  attr_grp; struct ds2780_device_info* drv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  get_property; int /*<<< orphan*/  num_properties; int /*<<< orphan*/  properties; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct ds2780_device_info {int /*<<< orphan*/  bat; TYPE_1__* dev; TYPE_2__ bat_desc; int /*<<< orphan*/  w1_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_BATTERY ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 struct ds2780_device_info* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_power_supply_register (TYPE_1__*,TYPE_2__*,struct power_supply_config*) ; 
 int /*<<< orphan*/  ds2780_battery_get_property ; 
 int /*<<< orphan*/  ds2780_battery_props ; 
 int /*<<< orphan*/  ds2780_sysfs_groups ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ds2780_device_info*) ; 

__attribute__((used)) static int ds2780_battery_probe(struct platform_device *pdev)
{
	struct power_supply_config psy_cfg = {};
	struct ds2780_device_info *dev_info;

	dev_info = devm_kzalloc(&pdev->dev, sizeof(*dev_info), GFP_KERNEL);
	if (!dev_info)
		return -ENOMEM;

	platform_set_drvdata(pdev, dev_info);

	dev_info->dev			= &pdev->dev;
	dev_info->w1_dev		= pdev->dev.parent;
	dev_info->bat_desc.name		= dev_name(&pdev->dev);
	dev_info->bat_desc.type		= POWER_SUPPLY_TYPE_BATTERY;
	dev_info->bat_desc.properties	= ds2780_battery_props;
	dev_info->bat_desc.num_properties = ARRAY_SIZE(ds2780_battery_props);
	dev_info->bat_desc.get_property	= ds2780_battery_get_property;

	psy_cfg.drv_data		= dev_info;
	psy_cfg.attr_grp		= ds2780_sysfs_groups;

	dev_info->bat = devm_power_supply_register(&pdev->dev,
						   &dev_info->bat_desc,
						   &psy_cfg);
	if (IS_ERR(dev_info->bat)) {
		dev_err(dev_info->dev, "failed to register battery\n");
		return PTR_ERR(dev_info->bat);
	}

	return 0;
}