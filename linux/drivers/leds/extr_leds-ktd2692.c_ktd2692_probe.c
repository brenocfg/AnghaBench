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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct led_classdev {int flags; int /*<<< orphan*/  name; int /*<<< orphan*/  brightness_set_blocking; int /*<<< orphan*/  max_brightness; } ;
struct led_classdev_flash {int /*<<< orphan*/ * ops; struct led_classdev led_cdev; } ;
struct ktd2692_led_config_data {int /*<<< orphan*/  max_brightness; } ;
struct ktd2692_context {int /*<<< orphan*/  lock; struct led_classdev_flash fled_cdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LED_CORE_SUSPENDRESUME ; 
 int LED_DEV_CAP_FLASH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct ktd2692_context* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flash_ops ; 
 int /*<<< orphan*/  ktd2692_init_flash_timeout (struct led_classdev_flash*,struct ktd2692_led_config_data*) ; 
 int /*<<< orphan*/  ktd2692_init_movie_current_max (struct ktd2692_led_config_data*) ; 
 int /*<<< orphan*/  ktd2692_led_brightness_set ; 
 int ktd2692_parse_dt (struct ktd2692_context*,int /*<<< orphan*/ *,struct ktd2692_led_config_data*) ; 
 int /*<<< orphan*/  ktd2692_setup (struct ktd2692_context*) ; 
 int led_classdev_flash_register (int /*<<< orphan*/ *,struct led_classdev_flash*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ktd2692_context*) ; 

__attribute__((used)) static int ktd2692_probe(struct platform_device *pdev)
{
	struct ktd2692_context *led;
	struct led_classdev *led_cdev;
	struct led_classdev_flash *fled_cdev;
	struct ktd2692_led_config_data led_cfg;
	int ret;

	led = devm_kzalloc(&pdev->dev, sizeof(*led), GFP_KERNEL);
	if (!led)
		return -ENOMEM;

	fled_cdev = &led->fled_cdev;
	led_cdev = &fled_cdev->led_cdev;

	ret = ktd2692_parse_dt(led, &pdev->dev, &led_cfg);
	if (ret)
		return ret;

	ktd2692_init_flash_timeout(fled_cdev, &led_cfg);
	ktd2692_init_movie_current_max(&led_cfg);

	fled_cdev->ops = &flash_ops;

	led_cdev->max_brightness = led_cfg.max_brightness;
	led_cdev->brightness_set_blocking = ktd2692_led_brightness_set;
	led_cdev->flags |= LED_CORE_SUSPENDRESUME | LED_DEV_CAP_FLASH;

	mutex_init(&led->lock);

	platform_set_drvdata(pdev, led);

	ret = led_classdev_flash_register(&pdev->dev, fled_cdev);
	if (ret) {
		dev_err(&pdev->dev, "can't register LED %s\n", led_cdev->name);
		mutex_destroy(&led->lock);
		return ret;
	}

	ktd2692_setup(led);

	return 0;
}