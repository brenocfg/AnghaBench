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
struct power_supply_config {struct asus_drvdata* drv_data; } ;
struct hid_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  uniq; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; scalar_t__ use_for_apm; int /*<<< orphan*/  type; int /*<<< orphan*/  get_property; int /*<<< orphan*/  num_properties; int /*<<< orphan*/  properties; } ;
struct asus_drvdata {int battery_in_query; int /*<<< orphan*/ * battery; TYPE_1__ battery_desc; int /*<<< orphan*/  battery_next_query; int /*<<< orphan*/  battery_stat; scalar_t__ battery_capacity; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_BATTERY ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asus_battery_get_property ; 
 int /*<<< orphan*/  asus_battery_props ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_kasprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_power_supply_register (int /*<<< orphan*/ *,TYPE_1__*,struct power_supply_config*) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 struct asus_drvdata* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  power_supply_powers (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asus_battery_probe(struct hid_device *hdev)
{
	struct asus_drvdata *drvdata = hid_get_drvdata(hdev);
	struct power_supply_config pscfg = { .drv_data = drvdata };
	int ret = 0;

	drvdata->battery_capacity = 0;
	drvdata->battery_stat = POWER_SUPPLY_STATUS_UNKNOWN;
	drvdata->battery_in_query = false;

	drvdata->battery_desc.properties = asus_battery_props;
	drvdata->battery_desc.num_properties = ARRAY_SIZE(asus_battery_props);
	drvdata->battery_desc.get_property = asus_battery_get_property;
	drvdata->battery_desc.type = POWER_SUPPLY_TYPE_BATTERY;
	drvdata->battery_desc.use_for_apm = 0;
	drvdata->battery_desc.name = devm_kasprintf(&hdev->dev, GFP_KERNEL,
					"asus-keyboard-%s-battery",
					strlen(hdev->uniq) ?
					hdev->uniq : dev_name(&hdev->dev));
	if (!drvdata->battery_desc.name)
		return -ENOMEM;

	drvdata->battery_next_query = jiffies;

	drvdata->battery = devm_power_supply_register(&hdev->dev,
				&(drvdata->battery_desc), &pscfg);
	if (IS_ERR(drvdata->battery)) {
		ret = PTR_ERR(drvdata->battery);
		drvdata->battery = NULL;
		hid_err(hdev, "Unable to register battery device\n");
		return ret;
	}

	power_supply_powers(drvdata->battery, &hdev->dev);

	return ret;
}