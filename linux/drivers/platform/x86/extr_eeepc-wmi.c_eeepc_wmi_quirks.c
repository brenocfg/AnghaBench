#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct asus_wmi_driver {int /*<<< orphan*/  panel_power; TYPE_1__* quirks; } ;
struct TYPE_3__ {int wapf; int /*<<< orphan*/  hotplug_wireless; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  asus_quirks ; 
 int /*<<< orphan*/  dmi_check_system (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hotplug_wireless ; 
 TYPE_1__ quirk_asus_unknown ; 
 TYPE_1__* quirks ; 

__attribute__((used)) static void eeepc_wmi_quirks(struct asus_wmi_driver *driver)
{
	quirks = &quirk_asus_unknown;
	quirks->hotplug_wireless = hotplug_wireless;

	dmi_check_system(asus_quirks);

	driver->quirks = quirks;
	driver->quirks->wapf = -1;
	driver->panel_power = FB_BLANK_UNBLANK;
}