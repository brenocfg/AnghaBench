#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct acpi_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_7__ {TYPE_4__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_KBD_LED ; 
 int /*<<< orphan*/  INIT_TPAD_LED ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_NONE ; 
 int /*<<< orphan*/  PLATFORM_NAME ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_attribute_group ; 
 int /*<<< orphan*/  inited ; 
 int /*<<< orphan*/  kbd_backlight ; 
 int /*<<< orphan*/  led_classdev_register (TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* pf_device ; 
 int /*<<< orphan*/  pf_driver ; 
 TYPE_1__* platform_device_register_simple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (TYPE_1__*) ; 
 int platform_driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpad_led ; 
 int /*<<< orphan*/  wmi_input_setup () ; 

__attribute__((used)) static int acpi_add(struct acpi_device *device)
{
	int ret;

	if (pf_device)
		return 0;

	ret = platform_driver_register(&pf_driver);
	if (ret)
		return ret;

	pf_device = platform_device_register_simple(PLATFORM_NAME,
						    PLATFORM_DEVID_NONE,
						    NULL, 0);
	if (IS_ERR(pf_device)) {
		ret = PTR_ERR(pf_device);
		pf_device = NULL;
		pr_err("unable to register platform device\n");
		goto out_platform_registered;
	}

	ret = sysfs_create_group(&pf_device->dev.kobj, &dev_attribute_group);
	if (ret)
		goto out_platform_device;

	if (!led_classdev_register(&pf_device->dev, &kbd_backlight))
		inited |= INIT_KBD_LED;

	if (!led_classdev_register(&pf_device->dev, &tpad_led))
		inited |= INIT_TPAD_LED;

	wmi_input_setup();

	return 0;

out_platform_device:
	platform_device_unregister(pf_device);
out_platform_registered:
	platform_driver_unregister(&pf_driver);
	return ret;
}