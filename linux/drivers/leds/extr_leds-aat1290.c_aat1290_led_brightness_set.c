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
struct led_classdev_flash {int dummy; } ;
struct led_classdev {int dummy; } ;
struct aat1290_led {int movie_mode; int /*<<< orphan*/  lock; int /*<<< orphan*/  gpio_en_set; int /*<<< orphan*/  gpio_fl_en; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int AAT1290_MAX_MM_CURR_PERCENT_0 ; 
 int /*<<< orphan*/  AAT1290_MM_CURRENT_RATIO_ADDR ; 
 int AAT1290_MM_TO_FL_1_92 ; 
 int /*<<< orphan*/  AAT1290_MOVIE_MODE_CONFIG_ADDR ; 
 int /*<<< orphan*/  AAT1290_MOVIE_MODE_CURRENT_ADDR ; 
 int AAT1290_MOVIE_MODE_ON ; 
 int /*<<< orphan*/  aat1290_as2cwire_write (struct aat1290_led*,int /*<<< orphan*/ ,int) ; 
 struct aat1290_led* fled_cdev_to_led (struct led_classdev_flash*) ; 
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct led_classdev_flash* led_cdev_to_fled_cdev (struct led_classdev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aat1290_led_brightness_set(struct led_classdev *led_cdev,
					enum led_brightness brightness)
{
	struct led_classdev_flash *fled_cdev = led_cdev_to_fled_cdev(led_cdev);
	struct aat1290_led *led = fled_cdev_to_led(fled_cdev);

	mutex_lock(&led->lock);

	if (brightness == 0) {
		gpiod_direction_output(led->gpio_fl_en, 0);
		gpiod_direction_output(led->gpio_en_set, 0);
		led->movie_mode = false;
	} else {
		if (!led->movie_mode) {
			aat1290_as2cwire_write(led,
				AAT1290_MM_CURRENT_RATIO_ADDR,
				AAT1290_MM_TO_FL_1_92);
			led->movie_mode = true;
		}

		aat1290_as2cwire_write(led, AAT1290_MOVIE_MODE_CURRENT_ADDR,
				AAT1290_MAX_MM_CURR_PERCENT_0 - brightness);
		aat1290_as2cwire_write(led, AAT1290_MOVIE_MODE_CONFIG_ADDR,
				AAT1290_MOVIE_MODE_ON);
	}

	mutex_unlock(&led->lock);

	return 0;
}