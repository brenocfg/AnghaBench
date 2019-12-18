#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {int id; TYPE_2__ dev; } ;
struct led_info {int /*<<< orphan*/  flags; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  brightness; int /*<<< orphan*/  brightness_set_blocking; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  name; } ;
struct da903x_led {int id; TYPE_1__ cdev; int /*<<< orphan*/  master; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int DA9030_ID_LED_1 ; 
 int DA9030_ID_VIBRA ; 
 int DA9034_ID_LED_1 ; 
 int DA9034_ID_VIBRA ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  da903x_led_set ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 struct led_info* dev_get_platdata (TYPE_2__*) ; 
 struct da903x_led* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_led_classdev_register (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int da903x_led_probe(struct platform_device *pdev)
{
	struct led_info *pdata = dev_get_platdata(&pdev->dev);
	struct da903x_led *led;
	int id, ret;

	if (pdata == NULL)
		return 0;

	id = pdev->id;

	if (!((id >= DA9030_ID_LED_1 && id <= DA9030_ID_VIBRA) ||
	      (id >= DA9034_ID_LED_1 && id <= DA9034_ID_VIBRA))) {
		dev_err(&pdev->dev, "invalid LED ID (%d) specified\n", id);
		return -EINVAL;
	}

	led = devm_kzalloc(&pdev->dev, sizeof(struct da903x_led), GFP_KERNEL);
	if (!led)
		return -ENOMEM;

	led->cdev.name = pdata->name;
	led->cdev.default_trigger = pdata->default_trigger;
	led->cdev.brightness_set_blocking = da903x_led_set;
	led->cdev.brightness = LED_OFF;

	led->id = id;
	led->flags = pdata->flags;
	led->master = pdev->dev.parent;

	ret = devm_led_classdev_register(led->master, &led->cdev);
	if (ret) {
		dev_err(&pdev->dev, "failed to register LED %d\n", id);
		return ret;
	}

	return 0;
}