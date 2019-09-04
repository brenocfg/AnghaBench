#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wm8994_pdata {int gpio_base; } ;
struct TYPE_6__ {int base; TYPE_2__* parent; int /*<<< orphan*/  ngpio; } ;
struct wm8994_gpio {TYPE_1__ gpio_chip; struct wm8994* wm8994; } ;
struct wm8994 {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WM8994_GPIO_MAX ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 struct wm8994* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct wm8994_pdata* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int devm_gpiochip_add_data (TYPE_2__*,TYPE_1__*,struct wm8994_gpio*) ; 
 struct wm8994_gpio* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct wm8994_gpio*) ; 
 TYPE_1__ template_chip ; 

__attribute__((used)) static int wm8994_gpio_probe(struct platform_device *pdev)
{
	struct wm8994 *wm8994 = dev_get_drvdata(pdev->dev.parent);
	struct wm8994_pdata *pdata = dev_get_platdata(wm8994->dev);
	struct wm8994_gpio *wm8994_gpio;
	int ret;

	wm8994_gpio = devm_kzalloc(&pdev->dev, sizeof(*wm8994_gpio),
				   GFP_KERNEL);
	if (wm8994_gpio == NULL)
		return -ENOMEM;

	wm8994_gpio->wm8994 = wm8994;
	wm8994_gpio->gpio_chip = template_chip;
	wm8994_gpio->gpio_chip.ngpio = WM8994_GPIO_MAX;
	wm8994_gpio->gpio_chip.parent = &pdev->dev;
	if (pdata && pdata->gpio_base)
		wm8994_gpio->gpio_chip.base = pdata->gpio_base;
	else
		wm8994_gpio->gpio_chip.base = -1;

	ret = devm_gpiochip_add_data(&pdev->dev, &wm8994_gpio->gpio_chip,
				     wm8994_gpio);
	if (ret < 0) {
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n",
			ret);
		return ret;
	}

	platform_set_drvdata(pdev, wm8994_gpio);

	return ret;
}