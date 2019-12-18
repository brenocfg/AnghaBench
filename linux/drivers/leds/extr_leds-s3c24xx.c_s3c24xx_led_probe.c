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
struct s3c24xx_led_platdata {int flags; int /*<<< orphan*/  gpio; int /*<<< orphan*/  name; int /*<<< orphan*/  def_trigger; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  brightness_set; } ;
struct s3c24xx_gpio_led {TYPE_1__ cdev; struct s3c24xx_led_platdata* pdata; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LED_CORE_SUSPENDRESUME ; 
 int S3C24XX_LEDF_ACTLOW ; 
 int S3C24XX_LEDF_TRISTATE ; 
 int /*<<< orphan*/  S3C_GPIO_PULL_NONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct s3c24xx_led_platdata* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int devm_gpio_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct s3c24xx_gpio_led* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_led_classdev_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s3c24xx_led_set ; 
 int /*<<< orphan*/  s3c_gpio_setpull (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c24xx_led_probe(struct platform_device *dev)
{
	struct s3c24xx_led_platdata *pdata = dev_get_platdata(&dev->dev);
	struct s3c24xx_gpio_led *led;
	int ret;

	led = devm_kzalloc(&dev->dev, sizeof(struct s3c24xx_gpio_led),
			   GFP_KERNEL);
	if (!led)
		return -ENOMEM;

	led->cdev.brightness_set = s3c24xx_led_set;
	led->cdev.default_trigger = pdata->def_trigger;
	led->cdev.name = pdata->name;
	led->cdev.flags |= LED_CORE_SUSPENDRESUME;

	led->pdata = pdata;

	ret = devm_gpio_request(&dev->dev, pdata->gpio, "S3C24XX_LED");
	if (ret < 0)
		return ret;

	/* no point in having a pull-up if we are always driving */

	s3c_gpio_setpull(pdata->gpio, S3C_GPIO_PULL_NONE);

	if (pdata->flags & S3C24XX_LEDF_TRISTATE)
		gpio_direction_input(pdata->gpio);
	else
		gpio_direction_output(pdata->gpio,
			pdata->flags & S3C24XX_LEDF_ACTLOW ? 1 : 0);

	/* register our new led device */

	ret = devm_led_classdev_register(&dev->dev, &led->cdev);
	if (ret < 0)
		dev_err(&dev->dev, "led_classdev_register failed\n");

	return ret;
}