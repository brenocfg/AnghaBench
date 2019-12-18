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
struct v4l2_flash_config {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct led_init_data {int /*<<< orphan*/  devicename; int /*<<< orphan*/  fwnode; } ;
struct led_classdev {int /*<<< orphan*/  flags; int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  brightness_set_blocking; } ;
struct led_classdev_flash {struct led_classdev led_cdev; int /*<<< orphan*/ * ops; } ;
struct device_node {int dummy; } ;
struct aat1290_led_config_data {int /*<<< orphan*/  max_brightness; } ;
struct aat1290_led {int /*<<< orphan*/  lock; int /*<<< orphan*/  v4l2_flash; struct led_classdev_flash fled_cdev; struct platform_device* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAT1290_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED_DEV_CAP_FLASH ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aat1290_init_flash_timeout (struct aat1290_led*,struct aat1290_led_config_data*) ; 
 int /*<<< orphan*/  aat1290_init_v4l2_flash_config (struct aat1290_led*,struct aat1290_led_config_data*,struct v4l2_flash_config*) ; 
 int /*<<< orphan*/  aat1290_led_brightness_set ; 
 int aat1290_led_get_configuration (struct aat1290_led*,struct aat1290_led_config_data*,struct device_node**) ; 
 struct aat1290_led* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flash_ops ; 
 int led_classdev_flash_register_ext (struct device*,struct led_classdev_flash*,struct led_init_data*) ; 
 int /*<<< orphan*/  led_classdev_flash_unregister (struct led_classdev_flash*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct aat1290_led*) ; 
 int /*<<< orphan*/  v4l2_flash_init (struct device*,int /*<<< orphan*/ ,struct led_classdev_flash*,int /*<<< orphan*/ *,struct v4l2_flash_config*) ; 
 int /*<<< orphan*/  v4l2_flash_ops ; 

__attribute__((used)) static int aat1290_led_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *sub_node = NULL;
	struct aat1290_led *led;
	struct led_classdev *led_cdev;
	struct led_classdev_flash *fled_cdev;
	struct led_init_data init_data = {};
	struct aat1290_led_config_data led_cfg = {};
	struct v4l2_flash_config v4l2_sd_cfg = {};
	int ret;

	led = devm_kzalloc(dev, sizeof(*led), GFP_KERNEL);
	if (!led)
		return -ENOMEM;

	led->pdev = pdev;
	platform_set_drvdata(pdev, led);

	fled_cdev = &led->fled_cdev;
	fled_cdev->ops = &flash_ops;
	led_cdev = &fled_cdev->led_cdev;

	ret = aat1290_led_get_configuration(led, &led_cfg, &sub_node);
	if (ret < 0)
		return ret;

	mutex_init(&led->lock);

	/* Initialize LED Flash class device */
	led_cdev->brightness_set_blocking = aat1290_led_brightness_set;
	led_cdev->max_brightness = led_cfg.max_brightness;
	led_cdev->flags |= LED_DEV_CAP_FLASH;

	aat1290_init_flash_timeout(led, &led_cfg);

	init_data.fwnode = of_fwnode_handle(sub_node);
	init_data.devicename = AAT1290_NAME;

	/* Register LED Flash class device */
	ret = led_classdev_flash_register_ext(&pdev->dev, fled_cdev,
					      &init_data);
	if (ret < 0)
		goto err_flash_register;

	aat1290_init_v4l2_flash_config(led, &led_cfg, &v4l2_sd_cfg);

	/* Create V4L2 Flash subdev. */
	led->v4l2_flash = v4l2_flash_init(dev, of_fwnode_handle(sub_node),
					  fled_cdev, &v4l2_flash_ops,
					  &v4l2_sd_cfg);
	if (IS_ERR(led->v4l2_flash)) {
		ret = PTR_ERR(led->v4l2_flash);
		goto error_v4l2_flash_init;
	}

	return 0;

error_v4l2_flash_init:
	led_classdev_flash_unregister(fled_cdev);
err_flash_register:
	mutex_destroy(&led->lock);

	return ret;
}