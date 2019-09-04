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
struct max77693_sub_led {int fled_id; scalar_t__ flash_timeout; } ;
struct max77693_led_device {scalar_t__ current_flash_timeout; int strobing_sub_led_id; int /*<<< orphan*/  lock; } ;
struct led_classdev_flash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_FLASH (int) ; 
 struct max77693_sub_led* flcdev_to_sub_led (struct led_classdev_flash*) ; 
 int max77693_add_mode (struct max77693_led_device*,int /*<<< orphan*/ ) ; 
 int max77693_clear_mode (struct max77693_led_device*,int /*<<< orphan*/ ) ; 
 int max77693_get_flash_faults (struct max77693_sub_led*) ; 
 int max77693_set_timeout (struct max77693_led_device*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct max77693_led_device* sub_led_to_led (struct max77693_sub_led*) ; 

__attribute__((used)) static int max77693_led_flash_strobe_set(
				struct led_classdev_flash *fled_cdev,
				bool state)
{
	struct max77693_sub_led *sub_led = flcdev_to_sub_led(fled_cdev);
	struct max77693_led_device *led = sub_led_to_led(sub_led);
	int fled_id = sub_led->fled_id;
	int ret;

	mutex_lock(&led->lock);

	if (!state) {
		ret = max77693_clear_mode(led, MODE_FLASH(fled_id));
		goto unlock;
	}

	if (sub_led->flash_timeout != led->current_flash_timeout) {
		ret = max77693_set_timeout(led, sub_led->flash_timeout);
		if (ret < 0)
			goto unlock;
	}

	led->strobing_sub_led_id = fled_id;

	ret = max77693_add_mode(led, MODE_FLASH(fled_id));
	if (ret < 0)
		goto unlock;

	ret = max77693_get_flash_faults(sub_led);

unlock:
	mutex_unlock(&led->lock);
	return ret;
}