#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ fwnode; } ;
struct platform_device {TYPE_2__ dev; } ;
struct gpio_backlight_platform_data {char* name; int /*<<< orphan*/  gpio; scalar_t__ def_value; int /*<<< orphan*/  fbdev; } ;
struct gpio_backlight {int /*<<< orphan*/  gpiod; TYPE_2__* dev; scalar_t__ def_value; int /*<<< orphan*/  fbdev; } ;
struct backlight_properties {int max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_9__ {int brightness; int /*<<< orphan*/  power; } ;
struct backlight_device {TYPE_1__ props; } ;
typedef  int /*<<< orphan*/  props ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long GPIOF_DIR_OUT ; 
 unsigned long GPIOF_INIT_HIGH ; 
 unsigned long GPIOF_INIT_LOW ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct gpio_backlight_platform_data* dev_get_platdata (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 struct backlight_device* devm_backlight_device_register (TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*,struct gpio_backlight*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 int devm_gpio_request_one (TYPE_2__*,int /*<<< orphan*/ ,unsigned long,char*) ; 
 struct gpio_backlight* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_backlight_initial_power_state (struct gpio_backlight*) ; 
 int /*<<< orphan*/  gpio_backlight_ops ; 
 int gpio_backlight_probe_dt (struct platform_device*,struct gpio_backlight*) ; 
 int /*<<< orphan*/  gpio_to_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct backlight_device*) ; 

__attribute__((used)) static int gpio_backlight_probe(struct platform_device *pdev)
{
	struct gpio_backlight_platform_data *pdata =
		dev_get_platdata(&pdev->dev);
	struct backlight_properties props;
	struct backlight_device *bl;
	struct gpio_backlight *gbl;
	int ret;

	gbl = devm_kzalloc(&pdev->dev, sizeof(*gbl), GFP_KERNEL);
	if (gbl == NULL)
		return -ENOMEM;

	gbl->dev = &pdev->dev;

	if (pdev->dev.fwnode) {
		ret = gpio_backlight_probe_dt(pdev, gbl);
		if (ret)
			return ret;
	} else if (pdata) {
		/*
		 * Legacy platform data GPIO retrieveal. Do not expand
		 * the use of this code path, currently only used by one
		 * SH board.
		 */
		unsigned long flags = GPIOF_DIR_OUT;

		gbl->fbdev = pdata->fbdev;
		gbl->def_value = pdata->def_value;
		flags |= gbl->def_value ? GPIOF_INIT_HIGH : GPIOF_INIT_LOW;

		ret = devm_gpio_request_one(gbl->dev, pdata->gpio, flags,
					    pdata ? pdata->name : "backlight");
		if (ret < 0) {
			dev_err(&pdev->dev, "unable to request GPIO\n");
			return ret;
		}
		gbl->gpiod = gpio_to_desc(pdata->gpio);
		if (!gbl->gpiod)
			return -EINVAL;
	} else {
		dev_err(&pdev->dev,
			"failed to find platform data or device tree node.\n");
		return -ENODEV;
	}

	memset(&props, 0, sizeof(props));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = 1;
	bl = devm_backlight_device_register(&pdev->dev, dev_name(&pdev->dev),
					&pdev->dev, gbl, &gpio_backlight_ops,
					&props);
	if (IS_ERR(bl)) {
		dev_err(&pdev->dev, "failed to register backlight\n");
		return PTR_ERR(bl);
	}

	bl->props.power = gpio_backlight_initial_power_state(gbl);
	bl->props.brightness = 1;

	backlight_update_status(bl);

	platform_set_drvdata(pdev, bl);
	return 0;
}