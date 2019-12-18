#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct asus_laptop {int ledd_status; int light_switch; int light_level; int /*<<< orphan*/  handle; scalar_t__ is_pega_lucid; void* wled_type; void* bled_type; TYPE_2__* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  present; } ;
struct TYPE_4__ {TYPE_1__ status; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  METHOD_ALS_CONTROL ; 
 int /*<<< orphan*/  METHOD_ALS_LEVEL ; 
 int /*<<< orphan*/  METHOD_KBD_LIGHT_SET ; 
 void* TYPE_LED ; 
 void* TYPE_RFKILL ; 
 int acpi_bus_get_status (TYPE_2__*) ; 
 int /*<<< orphan*/  acpi_check_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  als_status ; 
 int /*<<< orphan*/  asus_als_level (struct asus_laptop*,int) ; 
 int /*<<< orphan*/  asus_als_switch (struct asus_laptop*,int) ; 
 int /*<<< orphan*/  asus_bluetooth_set (struct asus_laptop*,int) ; 
 int /*<<< orphan*/  asus_kled_set (struct asus_laptop*,int) ; 
 int asus_laptop_get_info (struct asus_laptop*) ; 
 int /*<<< orphan*/  asus_wimax_set (struct asus_laptop*,int) ; 
 int /*<<< orphan*/  asus_wlan_set (struct asus_laptop*,int) ; 
 int /*<<< orphan*/  asus_wwan_set (struct asus_laptop*,int) ; 
 int /*<<< orphan*/  bled_type ; 
 scalar_t__ bluetooth_status ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wimax_status ; 
 scalar_t__ wlan_status ; 
 int /*<<< orphan*/  wled_type ; 
 scalar_t__ wwan_status ; 

__attribute__((used)) static int asus_acpi_init(struct asus_laptop *asus)
{
	int result = 0;

	result = acpi_bus_get_status(asus->device);
	if (result)
		return result;
	if (!asus->device->status.present) {
		pr_err("Hotkey device not present, aborting\n");
		return -ENODEV;
	}

	result = asus_laptop_get_info(asus);
	if (result)
		return result;

	if (!strcmp(bled_type, "led"))
		asus->bled_type = TYPE_LED;
	else if (!strcmp(bled_type, "rfkill"))
		asus->bled_type = TYPE_RFKILL;

	if (!strcmp(wled_type, "led"))
		asus->wled_type = TYPE_LED;
	else if (!strcmp(wled_type, "rfkill"))
		asus->wled_type = TYPE_RFKILL;

	if (bluetooth_status >= 0)
		asus_bluetooth_set(asus, !!bluetooth_status);

	if (wlan_status >= 0)
		asus_wlan_set(asus, !!wlan_status);

	if (wimax_status >= 0)
		asus_wimax_set(asus, !!wimax_status);

	if (wwan_status >= 0)
		asus_wwan_set(asus, !!wwan_status);

	/* Keyboard Backlight is on by default */
	if (!acpi_check_handle(asus->handle, METHOD_KBD_LIGHT_SET, NULL))
		asus_kled_set(asus, 1);

	/* LED display is off by default */
	asus->ledd_status = 0xFFF;

	/* Set initial values of light sensor and level */
	asus->light_switch = !!als_status;
	asus->light_level = 5;	/* level 5 for sensor sensitivity */

	if (asus->is_pega_lucid) {
		asus_als_switch(asus, asus->light_switch);
	} else if (!acpi_check_handle(asus->handle, METHOD_ALS_CONTROL, NULL) &&
		   !acpi_check_handle(asus->handle, METHOD_ALS_LEVEL, NULL)) {
		asus_als_switch(asus, asus->light_switch);
		asus_als_level(asus, asus->light_level);
	}

	return result;
}