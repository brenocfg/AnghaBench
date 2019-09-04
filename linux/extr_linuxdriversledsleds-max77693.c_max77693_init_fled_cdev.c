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
struct TYPE_2__ {int /*<<< orphan*/  val; } ;
struct led_classdev {int max_brightness; int /*<<< orphan*/  flags; int /*<<< orphan*/  brightness_set_blocking; int /*<<< orphan*/  name; } ;
struct led_classdev_flash {TYPE_1__ timeout; struct led_classdev led_cdev; int /*<<< orphan*/ * ops; } ;
struct max77693_sub_led {int fled_id; int /*<<< orphan*/  flash_timeout; struct led_classdev_flash fled_cdev; } ;
struct max77693_led_device {scalar_t__ iout_joint; } ;
struct max77693_led_config_data {int* iout_torch_max; int /*<<< orphan*/ * label; } ;

/* Variables and functions */
 size_t FLED1 ; 
 size_t FLED2 ; 
 int /*<<< orphan*/  LED_DEV_CAP_FLASH ; 
 int TORCH_IOUT_STEP ; 
 int /*<<< orphan*/  flash_ops ; 
 int /*<<< orphan*/  max77693_init_flash_settings (struct max77693_sub_led*,struct max77693_led_config_data*) ; 
 int /*<<< orphan*/  max77693_led_brightness_set ; 
 struct max77693_led_device* sub_led_to_led (struct max77693_sub_led*) ; 

__attribute__((used)) static void max77693_init_fled_cdev(struct max77693_sub_led *sub_led,
				struct max77693_led_config_data *led_cfg)
{
	struct max77693_led_device *led = sub_led_to_led(sub_led);
	int fled_id = sub_led->fled_id;
	struct led_classdev_flash *fled_cdev;
	struct led_classdev *led_cdev;

	/* Initialize LED Flash class device */
	fled_cdev = &sub_led->fled_cdev;
	fled_cdev->ops = &flash_ops;
	led_cdev = &fled_cdev->led_cdev;

	led_cdev->name = led_cfg->label[fled_id];

	led_cdev->brightness_set_blocking = max77693_led_brightness_set;
	led_cdev->max_brightness = (led->iout_joint ?
					led_cfg->iout_torch_max[FLED1] +
					led_cfg->iout_torch_max[FLED2] :
					led_cfg->iout_torch_max[fled_id]) /
				   TORCH_IOUT_STEP;
	led_cdev->flags |= LED_DEV_CAP_FLASH;

	max77693_init_flash_settings(sub_led, led_cfg);

	/* Init flash timeout cache */
	sub_led->flash_timeout = fled_cdev->timeout.val;
}