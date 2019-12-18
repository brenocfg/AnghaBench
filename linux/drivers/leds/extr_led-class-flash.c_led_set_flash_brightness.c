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
struct led_classdev {int flags; } ;
struct led_classdev_flash {struct led_flash_setting brightness; struct led_classdev led_cdev; } ;

/* Variables and functions */
 int LED_SUSPENDED ; 
 int call_flash_op (struct led_classdev_flash*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flash_brightness_set ; 
 int /*<<< orphan*/  led_clamp_align (struct led_flash_setting*) ; 

int led_set_flash_brightness(struct led_classdev_flash *fled_cdev,
				u32 brightness)
{
	struct led_classdev *led_cdev = &fled_cdev->led_cdev;
	struct led_flash_setting *s = &fled_cdev->brightness;

	s->val = brightness;
	led_clamp_align(s);

	if (!(led_cdev->flags & LED_SUSPENDED))
		return call_flash_op(fled_cdev, flash_brightness_set, s->val);

	return 0;
}