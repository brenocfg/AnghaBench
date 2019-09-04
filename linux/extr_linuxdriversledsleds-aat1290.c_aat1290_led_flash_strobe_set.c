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
struct led_flash_setting {int /*<<< orphan*/  val; } ;
struct led_classdev {scalar_t__ brightness; } ;
struct led_classdev_flash {struct led_flash_setting timeout; struct led_classdev led_cdev; } ;
struct aat1290_led {int movie_mode; int /*<<< orphan*/  lock; int /*<<< orphan*/  gpio_en_set; int /*<<< orphan*/  gpio_fl_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  aat1290_set_flash_safety_timer (struct aat1290_led*,int /*<<< orphan*/ ) ; 
 struct aat1290_led* fled_cdev_to_led (struct led_classdev_flash*) ; 
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aat1290_led_flash_strobe_set(struct led_classdev_flash *fled_cdev,
					 bool state)

{
	struct aat1290_led *led = fled_cdev_to_led(fled_cdev);
	struct led_classdev *led_cdev = &fled_cdev->led_cdev;
	struct led_flash_setting *timeout = &fled_cdev->timeout;

	mutex_lock(&led->lock);

	if (state) {
		aat1290_set_flash_safety_timer(led, timeout->val);
		gpiod_direction_output(led->gpio_fl_en, 1);
	} else {
		gpiod_direction_output(led->gpio_fl_en, 0);
		gpiod_direction_output(led->gpio_en_set, 0);
	}

	/*
	 * To reenter movie mode after a flash event the part must be cycled
	 * off and back on to reset the movie mode and reprogrammed via the
	 * AS2Cwire. Therefore the brightness and movie_mode properties needs
	 * to be updated here to reflect the actual state.
	 */
	led_cdev->brightness = 0;
	led->movie_mode = false;

	mutex_unlock(&led->lock);

	return 0;
}