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
struct TYPE_6__ {int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;
struct tps65218_gpio {TYPE_1__ gpio_chip; struct tps65218* tps65218; } ;
struct tps65218 {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 struct tps65218* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int devm_gpiochip_add_data (TYPE_2__*,TYPE_1__*,struct tps65218_gpio*) ; 
 struct tps65218_gpio* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tps65218_gpio*) ; 
 TYPE_1__ template_chip ; 

__attribute__((used)) static int tps65218_gpio_probe(struct platform_device *pdev)
{
	struct tps65218 *tps65218 = dev_get_drvdata(pdev->dev.parent);
	struct tps65218_gpio *tps65218_gpio;
	int ret;

	tps65218_gpio = devm_kzalloc(&pdev->dev, sizeof(*tps65218_gpio),
				     GFP_KERNEL);
	if (!tps65218_gpio)
		return -ENOMEM;

	tps65218_gpio->tps65218 = tps65218;
	tps65218_gpio->gpio_chip = template_chip;
	tps65218_gpio->gpio_chip.parent = &pdev->dev;
#ifdef CONFIG_OF_GPIO
	tps65218_gpio->gpio_chip.of_node = pdev->dev.of_node;
#endif

	ret = devm_gpiochip_add_data(&pdev->dev, &tps65218_gpio->gpio_chip,
				     tps65218_gpio);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to register gpiochip, %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, tps65218_gpio);

	return ret;
}