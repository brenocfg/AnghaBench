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
struct max77693_sub_led {int fled_id; } ;
struct max77693_led_device {int /*<<< orphan*/  lock; TYPE_1__* pdev; } ;
struct led_classdev_flash {int dummy; } ;
struct led_classdev {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_TORCH (int) ; 
 int TORCH_IOUT_STEP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 struct max77693_sub_led* flcdev_to_sub_led (struct led_classdev_flash*) ; 
 struct led_classdev_flash* lcdev_to_flcdev (struct led_classdev*) ; 
 int max77693_add_mode (struct max77693_led_device*,int /*<<< orphan*/ ) ; 
 int max77693_clear_mode (struct max77693_led_device*,int /*<<< orphan*/ ) ; 
 int max77693_set_torch_current (struct max77693_led_device*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct max77693_led_device* sub_led_to_led (struct max77693_sub_led*) ; 

__attribute__((used)) static int max77693_led_brightness_set(struct led_classdev *led_cdev,
					enum led_brightness value)
{
	struct led_classdev_flash *fled_cdev = lcdev_to_flcdev(led_cdev);
	struct max77693_sub_led *sub_led = flcdev_to_sub_led(fled_cdev);
	struct max77693_led_device *led = sub_led_to_led(sub_led);
	int fled_id = sub_led->fled_id, ret;

	mutex_lock(&led->lock);

	if (value == 0) {
		ret = max77693_clear_mode(led, MODE_TORCH(fled_id));
		if (ret < 0)
			dev_dbg(&led->pdev->dev,
				"Failed to clear torch mode (%d)\n",
				ret);
		goto unlock;
	}

	ret = max77693_set_torch_current(led, fled_id, value * TORCH_IOUT_STEP);
	if (ret < 0) {
		dev_dbg(&led->pdev->dev,
			"Failed to set torch current (%d)\n",
			ret);
		goto unlock;
	}

	ret = max77693_add_mode(led, MODE_TORCH(fled_id));
	if (ret < 0)
		dev_dbg(&led->pdev->dev,
			"Failed to set torch mode (%d)\n",
			ret);
unlock:
	mutex_unlock(&led->lock);

	return ret;
}