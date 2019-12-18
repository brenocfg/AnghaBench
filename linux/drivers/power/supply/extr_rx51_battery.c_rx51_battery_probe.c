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
struct TYPE_2__ {char* name; int /*<<< orphan*/  get_property; int /*<<< orphan*/  num_properties; int /*<<< orphan*/  properties; int /*<<< orphan*/  type; } ;
struct rx51_device_info {void* channel_temp; void* channel_bsi; void* channel_vbat; void* bat; TYPE_1__ bat_desc; int /*<<< orphan*/ * dev; } ;
struct power_supply_config {struct rx51_device_info* drv_data; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_BATTERY ; 
 int PTR_ERR (void*) ; 
 struct rx51_device_info* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* iio_channel_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iio_channel_release (void*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rx51_device_info*) ; 
 void* power_supply_register (int /*<<< orphan*/ *,TYPE_1__*,struct power_supply_config*) ; 
 int /*<<< orphan*/  rx51_battery_get_property ; 
 int /*<<< orphan*/  rx51_battery_props ; 

__attribute__((used)) static int rx51_battery_probe(struct platform_device *pdev)
{
	struct power_supply_config psy_cfg = {};
	struct rx51_device_info *di;
	int ret;

	di = devm_kzalloc(&pdev->dev, sizeof(*di), GFP_KERNEL);
	if (!di)
		return -ENOMEM;

	platform_set_drvdata(pdev, di);

	di->dev = &pdev->dev;
	di->bat_desc.name = "rx51-battery";
	di->bat_desc.type = POWER_SUPPLY_TYPE_BATTERY;
	di->bat_desc.properties = rx51_battery_props;
	di->bat_desc.num_properties = ARRAY_SIZE(rx51_battery_props);
	di->bat_desc.get_property = rx51_battery_get_property;

	psy_cfg.drv_data = di;

	di->channel_temp = iio_channel_get(di->dev, "temp");
	if (IS_ERR(di->channel_temp)) {
		ret = PTR_ERR(di->channel_temp);
		goto error;
	}

	di->channel_bsi  = iio_channel_get(di->dev, "bsi");
	if (IS_ERR(di->channel_bsi)) {
		ret = PTR_ERR(di->channel_bsi);
		goto error_channel_temp;
	}

	di->channel_vbat = iio_channel_get(di->dev, "vbat");
	if (IS_ERR(di->channel_vbat)) {
		ret = PTR_ERR(di->channel_vbat);
		goto error_channel_bsi;
	}

	di->bat = power_supply_register(di->dev, &di->bat_desc, &psy_cfg);
	if (IS_ERR(di->bat)) {
		ret = PTR_ERR(di->bat);
		goto error_channel_vbat;
	}

	return 0;

error_channel_vbat:
	iio_channel_release(di->channel_vbat);
error_channel_bsi:
	iio_channel_release(di->channel_bsi);
error_channel_temp:
	iio_channel_release(di->channel_temp);
error:

	return ret;
}