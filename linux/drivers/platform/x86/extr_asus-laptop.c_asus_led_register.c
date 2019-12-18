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
struct led_classdev {char const* name; int max_brightness; int /*<<< orphan*/  brightness_get; int /*<<< orphan*/  brightness_set; } ;
struct asus_led {char const* method; int /*<<< orphan*/  work; struct asus_laptop* asus; struct led_classdev led; } ;
struct asus_laptop {TYPE_1__* platform_device; int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_check_handle (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asus_led_cdev_get ; 
 int /*<<< orphan*/  asus_led_cdev_set ; 
 int /*<<< orphan*/  asus_led_cdev_update ; 
 int led_classdev_register (int /*<<< orphan*/ *,struct led_classdev*) ; 

__attribute__((used)) static int asus_led_register(struct asus_laptop *asus,
			     struct asus_led *led,
			     const char *name, const char *method)
{
	struct led_classdev *led_cdev = &led->led;

	if (!method || acpi_check_handle(asus->handle, method, NULL))
		return 0; /* Led not present */

	led->asus = asus;
	led->method = method;

	INIT_WORK(&led->work, asus_led_cdev_update);
	led_cdev->name = name;
	led_cdev->brightness_set = asus_led_cdev_set;
	led_cdev->brightness_get = asus_led_cdev_get;
	led_cdev->max_brightness = 1;
	return led_classdev_register(&asus->platform_device->dev, led_cdev);
}