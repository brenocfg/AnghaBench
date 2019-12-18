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
struct power_supply_desc {char* name; int /*<<< orphan*/  get_property; int /*<<< orphan*/  num_properties; int /*<<< orphan*/  properties; int /*<<< orphan*/  type; } ;
struct power_supply_config {int /*<<< orphan*/  of_node; struct ingenic_battery* drv_data; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {scalar_t__ voltage_min_design_uv; scalar_t__ voltage_max_design_uv; } ;
struct ingenic_battery {TYPE_1__ info; int /*<<< orphan*/  battery; struct power_supply_desc desc; int /*<<< orphan*/  channel; struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_BATTERY ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_iio_channel_get (struct device*,char*) ; 
 struct ingenic_battery* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_power_supply_register (struct device*,struct power_supply_desc*,struct power_supply_config*) ; 
 int /*<<< orphan*/  ingenic_battery_get_property ; 
 int /*<<< orphan*/  ingenic_battery_properties ; 
 int ingenic_battery_set_scale (struct ingenic_battery*) ; 
 int power_supply_get_battery_info (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int ingenic_battery_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct ingenic_battery *bat;
	struct power_supply_config psy_cfg = {};
	struct power_supply_desc *desc;
	int ret;

	bat = devm_kzalloc(dev, sizeof(*bat), GFP_KERNEL);
	if (!bat)
		return -ENOMEM;

	bat->dev = dev;
	bat->channel = devm_iio_channel_get(dev, "battery");
	if (IS_ERR(bat->channel))
		return PTR_ERR(bat->channel);

	desc = &bat->desc;
	desc->name = "jz-battery";
	desc->type = POWER_SUPPLY_TYPE_BATTERY;
	desc->properties = ingenic_battery_properties;
	desc->num_properties = ARRAY_SIZE(ingenic_battery_properties);
	desc->get_property = ingenic_battery_get_property;
	psy_cfg.drv_data = bat;
	psy_cfg.of_node = dev->of_node;

	bat->battery = devm_power_supply_register(dev, desc, &psy_cfg);
	if (IS_ERR(bat->battery)) {
		dev_err(dev, "Unable to register battery\n");
		return PTR_ERR(bat->battery);
	}

	ret = power_supply_get_battery_info(bat->battery, &bat->info);
	if (ret) {
		dev_err(dev, "Unable to get battery info: %d\n", ret);
		return ret;
	}
	if (bat->info.voltage_min_design_uv < 0) {
		dev_err(dev, "Unable to get voltage min design\n");
		return bat->info.voltage_min_design_uv;
	}
	if (bat->info.voltage_max_design_uv < 0) {
		dev_err(dev, "Unable to get voltage max design\n");
		return bat->info.voltage_max_design_uv;
	}

	return ingenic_battery_set_scale(bat);
}