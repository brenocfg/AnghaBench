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
struct max77693_sub_led {scalar_t__ fled_id; } ;
struct max77693_led_device {scalar_t__ strobing_sub_led_id; int /*<<< orphan*/  lock; } ;
struct led_classdev_flash {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct max77693_sub_led* flcdev_to_sub_led (struct led_classdev_flash*) ; 
 int max77693_get_strobe_status (struct max77693_led_device*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct max77693_led_device* sub_led_to_led (struct max77693_sub_led*) ; 

__attribute__((used)) static int max77693_led_flash_strobe_get(
				struct led_classdev_flash *fled_cdev,
				bool *state)
{
	struct max77693_sub_led *sub_led = flcdev_to_sub_led(fled_cdev);
	struct max77693_led_device *led = sub_led_to_led(sub_led);
	int ret;

	if (!state)
		return -EINVAL;

	mutex_lock(&led->lock);

	ret = max77693_get_strobe_status(led, state);

	*state = !!(*state && (led->strobing_sub_led_id == sub_led->fled_id));

	mutex_unlock(&led->lock);

	return ret;
}