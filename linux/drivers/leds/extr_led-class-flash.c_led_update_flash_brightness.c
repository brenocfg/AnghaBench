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
typedef  int /*<<< orphan*/  u32 ;
struct led_flash_setting {int /*<<< orphan*/  val; } ;
struct led_classdev_flash {struct led_flash_setting brightness; } ;

/* Variables and functions */
 int call_flash_op (struct led_classdev_flash*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flash_brightness_get ; 
 scalar_t__ has_flash_op (struct led_classdev_flash*,int /*<<< orphan*/ ) ; 

int led_update_flash_brightness(struct led_classdev_flash *fled_cdev)
{
	struct led_flash_setting *s = &fled_cdev->brightness;
	u32 brightness;

	if (has_flash_op(fled_cdev, flash_brightness_get)) {
		int ret = call_flash_op(fled_cdev, flash_brightness_get,
						&brightness);
		if (ret < 0)
			return ret;

		s->val = brightness;
	}

	return 0;
}