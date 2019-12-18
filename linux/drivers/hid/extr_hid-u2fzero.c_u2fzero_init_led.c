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
struct TYPE_4__ {int /*<<< orphan*/  brightness_set_blocking; int /*<<< orphan*/  flags; int /*<<< orphan*/  max_brightness; int /*<<< orphan*/ * name; } ;
struct u2fzero_device {TYPE_2__ ldev; TYPE_1__* hdev; int /*<<< orphan*/ * led_name; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_SHORT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LED_HW_PLUGGABLE ; 
 int /*<<< orphan*/  LED_ON ; 
 int /*<<< orphan*/ * devm_kasprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int devm_led_classdev_register (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  u2fzero_brightness_set ; 

__attribute__((used)) static int u2fzero_init_led(struct u2fzero_device *dev,
			    unsigned int minor)
{
	dev->led_name = devm_kasprintf(&dev->hdev->dev, GFP_KERNEL,
		"%s%u", DRIVER_SHORT, minor);
	if (dev->led_name == NULL)
		return -ENOMEM;

	dev->ldev.name = dev->led_name;
	dev->ldev.max_brightness = LED_ON;
	dev->ldev.flags = LED_HW_PLUGGABLE;
	dev->ldev.brightness_set_blocking = u2fzero_brightness_set;

	return devm_led_classdev_register(&dev->hdev->dev, &dev->ldev);
}