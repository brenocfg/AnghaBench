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
struct led_flash_setting {scalar_t__ max; scalar_t__ val; int /*<<< orphan*/  step; int /*<<< orphan*/  min; } ;
struct led_classdev_flash {struct led_flash_setting timeout; struct led_flash_setting brightness; } ;
struct max77693_sub_led {int fled_id; struct led_classdev_flash fled_cdev; } ;
struct max77693_led_device {scalar_t__ iout_joint; } ;
struct max77693_led_config_data {scalar_t__* flash_timeout_max; scalar_t__* iout_flash_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLASH_IOUT_MIN ; 
 int /*<<< orphan*/  FLASH_IOUT_STEP ; 
 int /*<<< orphan*/  FLASH_TIMEOUT_MIN ; 
 int /*<<< orphan*/  FLASH_TIMEOUT_STEP ; 
 size_t FLED1 ; 
 size_t FLED2 ; 
 struct max77693_led_device* sub_led_to_led (struct max77693_sub_led*) ; 

__attribute__((used)) static void max77693_init_flash_settings(struct max77693_sub_led *sub_led,
				 struct max77693_led_config_data *led_cfg)
{
	struct led_classdev_flash *fled_cdev = &sub_led->fled_cdev;
	struct max77693_led_device *led = sub_led_to_led(sub_led);
	int fled_id = sub_led->fled_id;
	struct led_flash_setting *setting;

	/* Init flash intensity setting */
	setting = &fled_cdev->brightness;
	setting->min = FLASH_IOUT_MIN;
	setting->max = led->iout_joint ?
		led_cfg->iout_flash_max[FLED1] +
		led_cfg->iout_flash_max[FLED2] :
		led_cfg->iout_flash_max[fled_id];
	setting->step = FLASH_IOUT_STEP;
	setting->val = setting->max;

	/* Init flash timeout setting */
	setting = &fled_cdev->timeout;
	setting->min = FLASH_TIMEOUT_MIN;
	setting->max = led_cfg->flash_timeout_max[fled_id];
	setting->step = FLASH_TIMEOUT_STEP;
	setting->val = setting->max;
}