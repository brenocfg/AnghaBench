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
struct platform_device {int dummy; } ;
struct max77693_sub_led {int /*<<< orphan*/  fled_cdev; int /*<<< orphan*/  v4l2_flash; } ;
struct max77693_led_device {int /*<<< orphan*/  lock; scalar_t__ iout_joint; struct max77693_sub_led* sub_leds; } ;

/* Variables and functions */
 size_t FLED1 ; 
 size_t FLED2 ; 
 int /*<<< orphan*/  led_classdev_flash_unregister (int /*<<< orphan*/ *) ; 
 scalar_t__ max77693_fled_used (struct max77693_led_device*,size_t) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct max77693_led_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  v4l2_flash_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max77693_led_remove(struct platform_device *pdev)
{
	struct max77693_led_device *led = platform_get_drvdata(pdev);
	struct max77693_sub_led *sub_leds = led->sub_leds;

	if (led->iout_joint || max77693_fled_used(led, FLED1)) {
		v4l2_flash_release(sub_leds[FLED1].v4l2_flash);
		led_classdev_flash_unregister(&sub_leds[FLED1].fled_cdev);
	}

	if (!led->iout_joint && max77693_fled_used(led, FLED2)) {
		v4l2_flash_release(sub_leds[FLED2].v4l2_flash);
		led_classdev_flash_unregister(&sub_leds[FLED2].fled_cdev);
	}

	mutex_destroy(&led->lock);

	return 0;
}