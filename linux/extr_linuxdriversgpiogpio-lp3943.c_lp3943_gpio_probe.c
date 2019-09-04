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
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_5__ {TYPE_2__* parent; } ;
struct lp3943_gpio {TYPE_1__ chip; struct lp3943* lp3943; } ;
struct lp3943 {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct lp3943* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int devm_gpiochip_add_data (TYPE_2__*,TYPE_1__*,struct lp3943_gpio*) ; 
 struct lp3943_gpio* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ lp3943_gpio_chip ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lp3943_gpio*) ; 

__attribute__((used)) static int lp3943_gpio_probe(struct platform_device *pdev)
{
	struct lp3943 *lp3943 = dev_get_drvdata(pdev->dev.parent);
	struct lp3943_gpio *lp3943_gpio;

	lp3943_gpio = devm_kzalloc(&pdev->dev, sizeof(*lp3943_gpio),
				GFP_KERNEL);
	if (!lp3943_gpio)
		return -ENOMEM;

	lp3943_gpio->lp3943 = lp3943;
	lp3943_gpio->chip = lp3943_gpio_chip;
	lp3943_gpio->chip.parent = &pdev->dev;

	platform_set_drvdata(pdev, lp3943_gpio);

	return devm_gpiochip_add_data(&pdev->dev, &lp3943_gpio->chip,
				      lp3943_gpio);
}