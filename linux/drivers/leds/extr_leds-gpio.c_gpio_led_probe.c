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
struct gpio_leds_priv {int num_leds; struct gpio_led_data* leds; } ;
struct gpio_led_platform_data {int num_leds; int /*<<< orphan*/  gpio_blink_set; struct gpio_led* leds; } ;
struct gpio_led_data {struct gpio_leds_priv* gpiod; } ;
struct gpio_led {int /*<<< orphan*/  name; int /*<<< orphan*/  gpio; struct gpio_leds_priv* gpiod; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct gpio_leds_priv*) ; 
 int PTR_ERR (struct gpio_leds_priv*) ; 
 int create_gpio_led (struct gpio_led const*,struct gpio_led_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct gpio_led_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gpio_leds_priv* devm_kzalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gpio_leds_priv* gpio_led_get_gpiod (int /*<<< orphan*/ *,int,struct gpio_led const*) ; 
 struct gpio_leds_priv* gpio_leds_create (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct gpio_leds_priv*) ; 
 int /*<<< orphan*/  sizeof_gpio_leds_priv (int) ; 

__attribute__((used)) static int gpio_led_probe(struct platform_device *pdev)
{
	struct gpio_led_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct gpio_leds_priv *priv;
	int i, ret = 0;

	if (pdata && pdata->num_leds) {
		priv = devm_kzalloc(&pdev->dev,
				sizeof_gpio_leds_priv(pdata->num_leds),
					GFP_KERNEL);
		if (!priv)
			return -ENOMEM;

		priv->num_leds = pdata->num_leds;
		for (i = 0; i < priv->num_leds; i++) {
			const struct gpio_led *template = &pdata->leds[i];
			struct gpio_led_data *led_dat = &priv->leds[i];

			if (template->gpiod)
				led_dat->gpiod = template->gpiod;
			else
				led_dat->gpiod =
					gpio_led_get_gpiod(&pdev->dev,
							   i, template);
			if (IS_ERR(led_dat->gpiod)) {
				dev_info(&pdev->dev, "Skipping unavailable LED gpio %d (%s)\n",
					 template->gpio, template->name);
				continue;
			}

			ret = create_gpio_led(template, led_dat,
					      &pdev->dev, NULL,
					      pdata->gpio_blink_set);
			if (ret < 0)
				return ret;
		}
	} else {
		priv = gpio_leds_create(pdev);
		if (IS_ERR(priv))
			return PTR_ERR(priv);
	}

	platform_set_drvdata(pdev, priv);

	return 0;
}