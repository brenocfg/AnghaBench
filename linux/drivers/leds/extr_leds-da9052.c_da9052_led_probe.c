#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_4__ dev; } ;
struct led_platform_data {int num_leds; TYPE_1__* leds; } ;
struct da9052_pdata {struct led_platform_data* pled; } ;
struct TYPE_7__ {int /*<<< orphan*/  brightness; int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  brightness_set_blocking; int /*<<< orphan*/  name; } ;
struct da9052_led {int led_index; TYPE_2__ cdev; void* da9052; } ;
struct da9052 {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_MAX_BRIGHTNESS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LED_OFF ; 
 int da9052_configure_leds (void*) ; 
 int /*<<< orphan*/  da9052_led_set ; 
 int da9052_set_led_brightness (struct da9052_led*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 void* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct da9052_pdata* dev_get_platdata (int /*<<< orphan*/ ) ; 
 struct da9052_led* devm_kcalloc (TYPE_4__*,int,int,int /*<<< orphan*/ ) ; 
 int led_classdev_register (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct da9052_led*) ; 

__attribute__((used)) static int da9052_led_probe(struct platform_device *pdev)
{
	struct da9052_pdata *pdata;
	struct da9052 *da9052;
	struct led_platform_data *pled;
	struct da9052_led *led = NULL;
	int error = -ENODEV;
	int i;

	da9052 = dev_get_drvdata(pdev->dev.parent);
	pdata = dev_get_platdata(da9052->dev);
	if (pdata == NULL) {
		dev_err(&pdev->dev, "No platform data\n");
		goto err;
	}

	pled = pdata->pled;
	if (pled == NULL) {
		dev_err(&pdev->dev, "No platform data for LED\n");
		goto err;
	}

	led = devm_kcalloc(&pdev->dev,
			   pled->num_leds, sizeof(struct da9052_led),
			   GFP_KERNEL);
	if (!led) {
		error = -ENOMEM;
		goto err;
	}

	for (i = 0; i < pled->num_leds; i++) {
		led[i].cdev.name = pled->leds[i].name;
		led[i].cdev.brightness_set_blocking = da9052_led_set;
		led[i].cdev.brightness = LED_OFF;
		led[i].cdev.max_brightness = DA9052_MAX_BRIGHTNESS;
		led[i].led_index = pled->leds[i].flags;
		led[i].da9052 = dev_get_drvdata(pdev->dev.parent);

		error = led_classdev_register(pdev->dev.parent, &led[i].cdev);
		if (error) {
			dev_err(&pdev->dev, "Failed to register led %d\n",
				led[i].led_index);
			goto err_register;
		}

		error = da9052_set_led_brightness(&led[i],
						  led[i].cdev.brightness);
		if (error) {
			dev_err(&pdev->dev, "Unable to init led %d\n",
				led[i].led_index);
			continue;
		}
	}
	error = da9052_configure_leds(led->da9052);
	if (error) {
		dev_err(&pdev->dev, "Failed to configure GPIO LED%d\n", error);
		goto err_register;
	}

	platform_set_drvdata(pdev, led);

	return 0;

err_register:
	for (i = i - 1; i >= 0; i--)
		led_classdev_unregister(&led[i].cdev);
err:
	return error;
}