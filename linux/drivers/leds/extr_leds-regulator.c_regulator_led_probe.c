#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ max_brightness; scalar_t__ name; scalar_t__ brightness; int /*<<< orphan*/  flags; int /*<<< orphan*/  (* brightness_set_blocking ) (TYPE_1__*,scalar_t__) ;} ;
struct regulator_led {int enabled; TYPE_1__ cdev; int /*<<< orphan*/  mutex; struct regulator* vcc; } ;
struct regulator {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct led_regulator_platform_data {scalar_t__ name; scalar_t__ brightness; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator*) ; 
 int /*<<< orphan*/  LED_CORE_SUSPENDRESUME ; 
 int PTR_ERR (struct regulator*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct led_regulator_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct regulator_led* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct regulator* devm_regulator_get_exclusive (int /*<<< orphan*/ *,char*) ; 
 int led_classdev_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ led_regulator_get_max_brightness (struct regulator*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct regulator_led*) ; 
 scalar_t__ regulator_is_enabled (struct regulator*) ; 
 int /*<<< orphan*/  regulator_led_brightness_set (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int regulator_led_probe(struct platform_device *pdev)
{
	struct led_regulator_platform_data *pdata =
			dev_get_platdata(&pdev->dev);
	struct regulator_led *led;
	struct regulator *vcc;
	int ret = 0;

	if (pdata == NULL) {
		dev_err(&pdev->dev, "no platform data\n");
		return -ENODEV;
	}

	vcc = devm_regulator_get_exclusive(&pdev->dev, "vled");
	if (IS_ERR(vcc)) {
		dev_err(&pdev->dev, "Cannot get vcc for %s\n", pdata->name);
		return PTR_ERR(vcc);
	}

	led = devm_kzalloc(&pdev->dev, sizeof(*led), GFP_KERNEL);
	if (led == NULL)
		return -ENOMEM;

	led->cdev.max_brightness = led_regulator_get_max_brightness(vcc);
	if (pdata->brightness > led->cdev.max_brightness) {
		dev_err(&pdev->dev, "Invalid default brightness %d\n",
				pdata->brightness);
		return -EINVAL;
	}

	led->cdev.brightness_set_blocking = regulator_led_brightness_set;
	led->cdev.name = pdata->name;
	led->cdev.flags |= LED_CORE_SUSPENDRESUME;
	led->vcc = vcc;

	/* to handle correctly an already enabled regulator */
	if (regulator_is_enabled(led->vcc))
		led->enabled = 1;

	mutex_init(&led->mutex);

	platform_set_drvdata(pdev, led);

	ret = led_classdev_register(&pdev->dev, &led->cdev);
	if (ret < 0)
		return ret;

	/* to expose the default value to userspace */
	led->cdev.brightness = pdata->brightness;

	/* Set the default led status */
	regulator_led_brightness_set(&led->cdev, led->cdev.brightness);

	return 0;
}