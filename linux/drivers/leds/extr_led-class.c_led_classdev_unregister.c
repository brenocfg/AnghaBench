#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct led_classdev {int flags; int /*<<< orphan*/  led_access; int /*<<< orphan*/  node; int /*<<< orphan*/  dev; int /*<<< orphan*/  set_brightness_work; int /*<<< orphan*/  trigger_lock; scalar_t__ trigger; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int LED_BRIGHT_HW_CHANGED ; 
 int /*<<< orphan*/  LED_OFF ; 
 int LED_UNREGISTERING ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_remove_brightness_hw_changed (struct led_classdev*) ; 
 int /*<<< orphan*/  led_set_brightness (struct led_classdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_stop_software_blink (struct led_classdev*) ; 
 int /*<<< orphan*/  led_trigger_set (struct led_classdev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leds_list_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void led_classdev_unregister(struct led_classdev *led_cdev)
{
	if (IS_ERR_OR_NULL(led_cdev->dev))
		return;

#ifdef CONFIG_LEDS_TRIGGERS
	down_write(&led_cdev->trigger_lock);
	if (led_cdev->trigger)
		led_trigger_set(led_cdev, NULL);
	up_write(&led_cdev->trigger_lock);
#endif

	led_cdev->flags |= LED_UNREGISTERING;

	/* Stop blinking */
	led_stop_software_blink(led_cdev);

	led_set_brightness(led_cdev, LED_OFF);

	flush_work(&led_cdev->set_brightness_work);

	if (led_cdev->flags & LED_BRIGHT_HW_CHANGED)
		led_remove_brightness_hw_changed(led_cdev);

	device_unregister(led_cdev->dev);

	down_write(&leds_list_lock);
	list_del(&led_cdev->node);
	up_write(&leds_list_lock);

	mutex_destroy(&led_cdev->led_access);
}