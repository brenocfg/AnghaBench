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
struct twl4030_madc_battery {void* channel_temp; void* channel_ichg; void* channel_vbat; void* psy; struct twl4030_madc_bat_platform_data* pdata; } ;
struct twl4030_madc_bat_platform_data {int /*<<< orphan*/  discharging_size; int /*<<< orphan*/  discharging; int /*<<< orphan*/  charging_size; int /*<<< orphan*/  charging; } ;
struct twl4030_madc_bat_calibration {int dummy; } ;
struct power_supply_config {struct twl4030_madc_battery* drv_data; } ;
struct TYPE_4__ {struct twl4030_madc_bat_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 struct twl4030_madc_battery* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 void* iio_channel_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  iio_channel_release (void*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct twl4030_madc_battery*) ; 
 void* power_supply_register (TYPE_1__*,int /*<<< orphan*/ *,struct power_supply_config*) ; 
 int /*<<< orphan*/  sort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  twl4030_cmp ; 
 int /*<<< orphan*/  twl4030_madc_bat_desc ; 

__attribute__((used)) static int twl4030_madc_battery_probe(struct platform_device *pdev)
{
	struct twl4030_madc_battery *twl4030_madc_bat;
	struct twl4030_madc_bat_platform_data *pdata = pdev->dev.platform_data;
	struct power_supply_config psy_cfg = {};
	int ret = 0;

	twl4030_madc_bat = devm_kzalloc(&pdev->dev, sizeof(*twl4030_madc_bat),
				GFP_KERNEL);
	if (!twl4030_madc_bat)
		return -ENOMEM;

	twl4030_madc_bat->channel_temp = iio_channel_get(&pdev->dev, "temp");
	if (IS_ERR(twl4030_madc_bat->channel_temp)) {
		ret = PTR_ERR(twl4030_madc_bat->channel_temp);
		goto err;
	}

	twl4030_madc_bat->channel_ichg = iio_channel_get(&pdev->dev, "ichg");
	if (IS_ERR(twl4030_madc_bat->channel_ichg)) {
		ret = PTR_ERR(twl4030_madc_bat->channel_ichg);
		goto err_temp;
	}

	twl4030_madc_bat->channel_vbat = iio_channel_get(&pdev->dev, "vbat");
	if (IS_ERR(twl4030_madc_bat->channel_vbat)) {
		ret = PTR_ERR(twl4030_madc_bat->channel_vbat);
		goto err_ichg;
	}

	/* sort charging and discharging calibration data */
	sort(pdata->charging, pdata->charging_size,
		sizeof(struct twl4030_madc_bat_calibration),
		twl4030_cmp, NULL);
	sort(pdata->discharging, pdata->discharging_size,
		sizeof(struct twl4030_madc_bat_calibration),
		twl4030_cmp, NULL);

	twl4030_madc_bat->pdata = pdata;
	platform_set_drvdata(pdev, twl4030_madc_bat);
	psy_cfg.drv_data = twl4030_madc_bat;
	twl4030_madc_bat->psy = power_supply_register(&pdev->dev,
						      &twl4030_madc_bat_desc,
						      &psy_cfg);
	if (IS_ERR(twl4030_madc_bat->psy)) {
		ret = PTR_ERR(twl4030_madc_bat->psy);
		goto err_vbat;
	}

	return 0;

err_vbat:
	iio_channel_release(twl4030_madc_bat->channel_vbat);
err_ichg:
	iio_channel_release(twl4030_madc_bat->channel_ichg);
err_temp:
	iio_channel_release(twl4030_madc_bat->channel_temp);
err:
	return ret;
}