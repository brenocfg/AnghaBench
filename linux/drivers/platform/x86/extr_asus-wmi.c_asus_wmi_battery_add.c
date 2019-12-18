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
struct power_supply {int /*<<< orphan*/  dev; TYPE_1__* desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_RSOC ; 
 int ENODEV ; 
 int /*<<< orphan*/  asus_wmi_set_devstate (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int charge_end_threshold ; 
 int /*<<< orphan*/  dev_attr_charge_control_end_threshold ; 
 scalar_t__ device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int asus_wmi_battery_add(struct power_supply *battery)
{
	/* The WMI method does not provide a way to specific a battery, so we
	 * just assume it is the first battery.
	 */
	if (strcmp(battery->desc->name, "BAT0") != 0)
		return -ENODEV;

	if (device_create_file(&battery->dev,
	    &dev_attr_charge_control_end_threshold))
		return -ENODEV;

	/* The charge threshold is only reset when the system is power cycled,
	 * and we can't get the current threshold so let set it to 100% when
	 * a battery is added.
	 */
	asus_wmi_set_devstate(ASUS_WMI_DEVID_RSOC, 100, NULL);
	charge_end_threshold = 100;

	return 0;
}