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
struct led_netdev_data {int /*<<< orphan*/  work; int /*<<< orphan*/  mode; struct led_classdev* led_cdev; } ;
struct led_classdev {int brightness; int blink_brightness; int max_brightness; } ;

/* Variables and functions */
 int LED_OFF ; 
 int /*<<< orphan*/  NETDEV_LED_LINK ; 
 int /*<<< orphan*/  NETDEV_LED_MODE_LINKUP ; 
 int /*<<< orphan*/  NETDEV_LED_RX ; 
 int /*<<< orphan*/  NETDEV_LED_TX ; 
 int /*<<< orphan*/  led_set_brightness (struct led_classdev*,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_baseline_state(struct led_netdev_data *trigger_data)
{
	int current_brightness;
	struct led_classdev *led_cdev = trigger_data->led_cdev;

	current_brightness = led_cdev->brightness;
	if (current_brightness)
		led_cdev->blink_brightness = current_brightness;
	if (!led_cdev->blink_brightness)
		led_cdev->blink_brightness = led_cdev->max_brightness;

	if (!test_bit(NETDEV_LED_MODE_LINKUP, &trigger_data->mode))
		led_set_brightness(led_cdev, LED_OFF);
	else {
		if (test_bit(NETDEV_LED_LINK, &trigger_data->mode))
			led_set_brightness(led_cdev,
					   led_cdev->blink_brightness);
		else
			led_set_brightness(led_cdev, LED_OFF);

		/* If we are looking for RX/TX start periodically
		 * checking stats
		 */
		if (test_bit(NETDEV_LED_TX, &trigger_data->mode) ||
		    test_bit(NETDEV_LED_RX, &trigger_data->mode))
			schedule_delayed_work(&trigger_data->work, 0);
	}
}