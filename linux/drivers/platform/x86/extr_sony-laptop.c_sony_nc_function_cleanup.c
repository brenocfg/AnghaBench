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
struct platform_device {int dummy; } ;
struct TYPE_2__ {unsigned int* cap; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 TYPE_1__* handles ; 
 int /*<<< orphan*/  sony_nc_acpi_handle ; 
 int /*<<< orphan*/  sony_nc_battery_care_cleanup (struct platform_device*) ; 
 int /*<<< orphan*/  sony_nc_fanspeed_cleanup (struct platform_device*) ; 
 int /*<<< orphan*/  sony_nc_gfx_switch_cleanup (struct platform_device*) ; 
 int /*<<< orphan*/  sony_nc_handles_cleanup (struct platform_device*) ; 
 int /*<<< orphan*/  sony_nc_highspeed_charging_cleanup (struct platform_device*) ; 
 int /*<<< orphan*/  sony_nc_int_call (int /*<<< orphan*/ ,char*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  sony_nc_kbd_backlight_cleanup (struct platform_device*,unsigned int) ; 
 int /*<<< orphan*/  sony_nc_lid_resume_cleanup (struct platform_device*) ; 
 int /*<<< orphan*/  sony_nc_lowbatt_cleanup (struct platform_device*) ; 
 int /*<<< orphan*/  sony_nc_panelid_cleanup (struct platform_device*) ; 
 int /*<<< orphan*/  sony_nc_rfkill_cleanup () ; 
 int /*<<< orphan*/  sony_nc_smart_conn_cleanup (struct platform_device*) ; 
 int /*<<< orphan*/  sony_nc_thermal_cleanup (struct platform_device*) ; 
 int /*<<< orphan*/  sony_nc_touchpad_cleanup (struct platform_device*) ; 
 int /*<<< orphan*/  sony_nc_usb_charge_cleanup (struct platform_device*) ; 

__attribute__((used)) static void sony_nc_function_cleanup(struct platform_device *pd)
{
	unsigned int i, result, bitmask, handle;

	if (!handles)
		return;

	/* get enabled events and disable them */
	sony_nc_int_call(sony_nc_acpi_handle, "SN01", NULL, &bitmask);
	sony_nc_int_call(sony_nc_acpi_handle, "SN03", &bitmask, &result);

	/* cleanup handles here */
	for (i = 0; i < ARRAY_SIZE(handles->cap); i++) {

		handle = handles->cap[i];

		if (!handle)
			continue;

		switch (handle) {
		case 0x0105:
		case 0x0148:
			sony_nc_touchpad_cleanup(pd);
			break;
		case 0x0115:
		case 0x0136:
		case 0x013f:
			sony_nc_battery_care_cleanup(pd);
			break;
		case 0x0119:
		case 0x015D:
			sony_nc_lid_resume_cleanup(pd);
			break;
		case 0x0122:
			sony_nc_thermal_cleanup(pd);
			break;
		case 0x0128:
		case 0x0146:
		case 0x015B:
			sony_nc_gfx_switch_cleanup(pd);
			break;
		case 0x0131:
			sony_nc_highspeed_charging_cleanup(pd);
			break;
		case 0x0124:
		case 0x0135:
			sony_nc_rfkill_cleanup();
			break;
		case 0x0137:
		case 0x0143:
		case 0x014b:
		case 0x014c:
		case 0x0153:
		case 0x0163:
			sony_nc_kbd_backlight_cleanup(pd, handle);
			break;
		case 0x0121:
			sony_nc_lowbatt_cleanup(pd);
			break;
		case 0x0149:
			sony_nc_fanspeed_cleanup(pd);
			break;
		case 0x0155:
			sony_nc_usb_charge_cleanup(pd);
			break;
		case 0x011D:
			sony_nc_panelid_cleanup(pd);
			break;
		case 0x0168:
			sony_nc_smart_conn_cleanup(pd);
			break;
		default:
			continue;
		}
	}

	/* finally cleanup the handles list */
	sony_nc_handles_cleanup(pd);
}