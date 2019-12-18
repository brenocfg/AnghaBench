#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct acpi_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int INIT_KBD_LED ; 
 int INIT_TPAD_LED ; 
 int /*<<< orphan*/  dev_attribute_group ; 
 int inited ; 
 int /*<<< orphan*/  kbd_backlight ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 TYPE_2__* pf_device ; 
 int /*<<< orphan*/  pf_driver ; 
 int /*<<< orphan*/  platform_device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpad_led ; 
 int /*<<< orphan*/  wmi_input_destroy () ; 

__attribute__((used)) static int acpi_remove(struct acpi_device *device)
{
	sysfs_remove_group(&pf_device->dev.kobj, &dev_attribute_group);
	if (inited & INIT_KBD_LED)
		led_classdev_unregister(&kbd_backlight);

	if (inited & INIT_TPAD_LED)
		led_classdev_unregister(&tpad_led);

	wmi_input_destroy();
	platform_device_unregister(pf_device);
	pf_device = NULL;
	platform_driver_unregister(&pf_driver);

	return 0;
}