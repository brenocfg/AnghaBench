#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct led_classdev {int /*<<< orphan*/  flags; int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  brightness_set_blocking; int /*<<< orphan*/  name; } ;
struct led_flash_setting {int /*<<< orphan*/  val; int /*<<< orphan*/  step; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_4__ {struct led_classdev led_cdev; struct led_flash_setting brightness; struct led_flash_setting timeout; int /*<<< orphan*/ * ops; } ;
struct lm3601x_led {TYPE_2__ fled_cdev; TYPE_1__* client; int /*<<< orphan*/  torch_current_max; int /*<<< orphan*/  led_name; int /*<<< orphan*/  flash_current_max; int /*<<< orphan*/  max_flash_timeout; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED_DEV_CAP_FLASH ; 
 int /*<<< orphan*/  LM3601X_LOWER_STEP_US ; 
 int /*<<< orphan*/  LM3601X_MIN_STROBE_I_UA ; 
 int /*<<< orphan*/  LM3601X_MIN_TIMEOUT_US ; 
 int /*<<< orphan*/  LM3601X_TORCH_REG_DIV ; 
 int /*<<< orphan*/  flash_ops ; 
 int led_classdev_flash_register (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  lm3601x_brightness_set ; 

__attribute__((used)) static int lm3601x_register_leds(struct lm3601x_led *led)
{
	struct led_classdev *led_cdev;
	struct led_flash_setting *setting;

	led->fled_cdev.ops = &flash_ops;

	setting = &led->fled_cdev.timeout;
	setting->min = LM3601X_MIN_TIMEOUT_US;
	setting->max = led->max_flash_timeout;
	setting->step = LM3601X_LOWER_STEP_US;
	setting->val = led->max_flash_timeout;

	setting = &led->fled_cdev.brightness;
	setting->min = LM3601X_MIN_STROBE_I_UA;
	setting->max = led->flash_current_max;
	setting->step = LM3601X_TORCH_REG_DIV;
	setting->val = led->flash_current_max;

	led_cdev = &led->fled_cdev.led_cdev;
	led_cdev->name = led->led_name;
	led_cdev->brightness_set_blocking = lm3601x_brightness_set;
	led_cdev->max_brightness = DIV_ROUND_UP(led->torch_current_max,
						LM3601X_TORCH_REG_DIV);
	led_cdev->flags |= LED_DEV_CAP_FLASH;

	return led_classdev_flash_register(&led->client->dev, &led->fled_cdev);
}