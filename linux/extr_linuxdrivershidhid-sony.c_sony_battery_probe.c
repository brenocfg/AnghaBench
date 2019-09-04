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
struct TYPE_2__ {int /*<<< orphan*/  name; scalar_t__ use_for_apm; int /*<<< orphan*/  type; int /*<<< orphan*/  get_property; int /*<<< orphan*/  num_properties; int /*<<< orphan*/  properties; } ;
struct sony_sc {int battery_capacity; int /*<<< orphan*/  battery; TYPE_1__ battery_desc; int /*<<< orphan*/  device_id; int /*<<< orphan*/  mac_address; struct hid_device* hdev; } ;
struct power_supply_config {struct sony_sc* drv_data; } ;
struct hid_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_BATTERY ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kasprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_power_supply_register (int /*<<< orphan*/ *,TYPE_1__*,struct power_supply_config*) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int /*<<< orphan*/  power_supply_powers (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sony_battery_get_property ; 
 int /*<<< orphan*/  sony_battery_props ; 

__attribute__((used)) static int sony_battery_probe(struct sony_sc *sc, int append_dev_id)
{
	const char *battery_str_fmt = append_dev_id ?
		"sony_controller_battery_%pMR_%i" :
		"sony_controller_battery_%pMR";
	struct power_supply_config psy_cfg = { .drv_data = sc, };
	struct hid_device *hdev = sc->hdev;
	int ret;

	/*
	 * Set the default battery level to 100% to avoid low battery warnings
	 * if the battery is polled before the first device report is received.
	 */
	sc->battery_capacity = 100;

	sc->battery_desc.properties = sony_battery_props;
	sc->battery_desc.num_properties = ARRAY_SIZE(sony_battery_props);
	sc->battery_desc.get_property = sony_battery_get_property;
	sc->battery_desc.type = POWER_SUPPLY_TYPE_BATTERY;
	sc->battery_desc.use_for_apm = 0;
	sc->battery_desc.name = devm_kasprintf(&hdev->dev, GFP_KERNEL,
					  battery_str_fmt, sc->mac_address, sc->device_id);
	if (!sc->battery_desc.name)
		return -ENOMEM;

	sc->battery = devm_power_supply_register(&hdev->dev, &sc->battery_desc,
					    &psy_cfg);
	if (IS_ERR(sc->battery)) {
		ret = PTR_ERR(sc->battery);
		hid_err(hdev, "Unable to register battery device\n");
		return ret;
	}

	power_supply_powers(sc->battery, &hdev->dev);
	return 0;
}