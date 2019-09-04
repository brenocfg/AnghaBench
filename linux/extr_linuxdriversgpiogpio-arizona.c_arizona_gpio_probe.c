#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct arizona_pdata {int gpio_base; } ;
struct TYPE_7__ {int ngpio; int base; TYPE_2__* parent; } ;
struct arizona_gpio {TYPE_1__ gpio_chip; struct arizona* arizona; } ;
struct arizona {int type; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CS47L24 135 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  WM1814 134 
#define  WM1831 133 
#define  WM5102 132 
#define  WM5110 131 
#define  WM8280 130 
#define  WM8997 129 
#define  WM8998 128 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 struct arizona* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct arizona_pdata* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int devm_gpiochip_add_data (TYPE_2__*,TYPE_1__*,struct arizona_gpio*) ; 
 struct arizona_gpio* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 TYPE_1__ template_chip ; 

__attribute__((used)) static int arizona_gpio_probe(struct platform_device *pdev)
{
	struct arizona *arizona = dev_get_drvdata(pdev->dev.parent);
	struct arizona_pdata *pdata = dev_get_platdata(arizona->dev);
	struct arizona_gpio *arizona_gpio;
	int ret;

	arizona_gpio = devm_kzalloc(&pdev->dev, sizeof(*arizona_gpio),
				    GFP_KERNEL);
	if (!arizona_gpio)
		return -ENOMEM;

	arizona_gpio->arizona = arizona;
	arizona_gpio->gpio_chip = template_chip;
	arizona_gpio->gpio_chip.parent = &pdev->dev;
#ifdef CONFIG_OF_GPIO
	arizona_gpio->gpio_chip.of_node = arizona->dev->of_node;
#endif

	switch (arizona->type) {
	case WM5102:
	case WM5110:
	case WM8280:
	case WM8997:
	case WM8998:
	case WM1814:
		arizona_gpio->gpio_chip.ngpio = 5;
		break;
	case WM1831:
	case CS47L24:
		arizona_gpio->gpio_chip.ngpio = 2;
		break;
	default:
		dev_err(&pdev->dev, "Unknown chip variant %d\n",
			arizona->type);
		return -EINVAL;
	}

	if (pdata && pdata->gpio_base)
		arizona_gpio->gpio_chip.base = pdata->gpio_base;
	else
		arizona_gpio->gpio_chip.base = -1;

	pm_runtime_enable(&pdev->dev);

	ret = devm_gpiochip_add_data(&pdev->dev, &arizona_gpio->gpio_chip,
				     arizona_gpio);
	if (ret < 0) {
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n",
			ret);
		return ret;
	}

	return 0;
}