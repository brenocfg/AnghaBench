#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wm831x_pdata {int gpio_base; } ;
struct TYPE_8__ {int base; int /*<<< orphan*/  of_node; TYPE_3__* parent; int /*<<< orphan*/  ngpio; } ;
struct wm831x_gpio {TYPE_2__ gpio_chip; struct wm831x* wm831x; } ;
struct wm831x {TYPE_1__* dev; int /*<<< orphan*/  num_gpio; struct wm831x_pdata pdata; } ;
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 struct wm831x* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int devm_gpiochip_add_data (TYPE_3__*,TYPE_2__*,struct wm831x_gpio*) ; 
 struct wm831x_gpio* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct wm831x_gpio*) ; 
 TYPE_2__ template_chip ; 

__attribute__((used)) static int wm831x_gpio_probe(struct platform_device *pdev)
{
	struct wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	struct wm831x_pdata *pdata = &wm831x->pdata;
	struct wm831x_gpio *wm831x_gpio;
	int ret;

	wm831x_gpio = devm_kzalloc(&pdev->dev, sizeof(*wm831x_gpio),
				   GFP_KERNEL);
	if (wm831x_gpio == NULL)
		return -ENOMEM;

	wm831x_gpio->wm831x = wm831x;
	wm831x_gpio->gpio_chip = template_chip;
	wm831x_gpio->gpio_chip.ngpio = wm831x->num_gpio;
	wm831x_gpio->gpio_chip.parent = &pdev->dev;
	if (pdata && pdata->gpio_base)
		wm831x_gpio->gpio_chip.base = pdata->gpio_base;
	else
		wm831x_gpio->gpio_chip.base = -1;
#ifdef CONFIG_OF_GPIO
	wm831x_gpio->gpio_chip.of_node = wm831x->dev->of_node;
#endif

	ret = devm_gpiochip_add_data(&pdev->dev, &wm831x_gpio->gpio_chip,
				     wm831x_gpio);
	if (ret < 0) {
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, wm831x_gpio);

	return ret;
}