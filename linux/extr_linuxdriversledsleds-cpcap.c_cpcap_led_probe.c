#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct of_device_id {TYPE_1__* data; } ;
struct TYPE_11__ {int /*<<< orphan*/  brightness_set_blocking; int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  name; } ;
struct cpcap_led {TYPE_2__* dev; TYPE_5__ led; TYPE_1__* info; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  regmap; int /*<<< orphan*/  vdd; } ;
struct TYPE_9__ {int reg; int /*<<< orphan*/  limit; int /*<<< orphan*/  init_val; scalar_t__ init_mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpcap_led_of_match ; 
 int /*<<< orphan*/  cpcap_led_set ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int device_property_read_string (TYPE_2__*,char*,int /*<<< orphan*/ *) ; 
 struct cpcap_led* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_led_classdev_register (TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  devm_regulator_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cpcap_led*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpcap_led_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	struct cpcap_led *led;
	int err;

	match = of_match_device(of_match_ptr(cpcap_led_of_match), &pdev->dev);
	if (!match || !match->data)
		return -EINVAL;

	led = devm_kzalloc(&pdev->dev, sizeof(*led), GFP_KERNEL);
	if (!led)
		return -ENOMEM;
	platform_set_drvdata(pdev, led);
	led->info = match->data;
	led->dev = &pdev->dev;

	if (led->info->reg == 0x0000) {
		dev_err(led->dev, "Unsupported LED");
		return -ENODEV;
	}

	led->regmap = dev_get_regmap(pdev->dev.parent, NULL);
	if (!led->regmap)
		return -ENODEV;

	led->vdd = devm_regulator_get(&pdev->dev, "vdd");
	if (IS_ERR(led->vdd)) {
		err = PTR_ERR(led->vdd);
		dev_err(led->dev, "Couldn't get regulator: %d", err);
		return err;
	}

	err = device_property_read_string(&pdev->dev, "label", &led->led.name);
	if (err) {
		dev_err(led->dev, "Couldn't read LED label: %d", err);
		return err;
	}

	if (led->info->init_mask) {
		err = regmap_update_bits(led->regmap, led->info->reg,
			led->info->init_mask, led->info->init_val);
		if (err) {
			dev_err(led->dev, "regmap failed: %d", err);
			return err;
		}
	}

	mutex_init(&led->update_lock);

	led->led.max_brightness = led->info->limit;
	led->led.brightness_set_blocking = cpcap_led_set;
	err = devm_led_classdev_register(&pdev->dev, &led->led);
	if (err) {
		dev_err(led->dev, "Couldn't register LED: %d", err);
		return err;
	}

	return 0;
}