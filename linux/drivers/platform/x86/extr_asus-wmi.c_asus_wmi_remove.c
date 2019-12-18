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
struct asus_wmi {int /*<<< orphan*/  platform_device; TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_guid; } ;

/* Variables and functions */
 int /*<<< orphan*/  asus_fan_set_auto (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_wmi_backlight_exit (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_wmi_battery_exit (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_wmi_debugfs_exit (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_wmi_input_exit (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_wmi_led_exit (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_wmi_rfkill_exit (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_wmi_sysfs_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct asus_wmi*) ; 
 struct asus_wmi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  wmi_remove_notify_handler (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asus_wmi_remove(struct platform_device *device)
{
	struct asus_wmi *asus;

	asus = platform_get_drvdata(device);
	wmi_remove_notify_handler(asus->driver->event_guid);
	asus_wmi_backlight_exit(asus);
	asus_wmi_input_exit(asus);
	asus_wmi_led_exit(asus);
	asus_wmi_rfkill_exit(asus);
	asus_wmi_debugfs_exit(asus);
	asus_wmi_sysfs_exit(asus->platform_device);
	asus_fan_set_auto(asus);
	asus_wmi_battery_exit(asus);

	kfree(asus);
	return 0;
}