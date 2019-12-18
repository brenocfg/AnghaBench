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
struct gpio_chip {int dummy; } ;
struct ep93xx_gpio_bank {int /*<<< orphan*/  label; } ;
struct ep93xx_gpio {struct gpio_chip* gc; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ep93xx_gpio_bank*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct ep93xx_gpio* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ ep93xx_gpio_add_bank (struct gpio_chip*,struct platform_device*,struct ep93xx_gpio*,struct ep93xx_gpio_bank*) ; 
 struct ep93xx_gpio_bank* ep93xx_gpio_banks ; 

__attribute__((used)) static int ep93xx_gpio_probe(struct platform_device *pdev)
{
	struct ep93xx_gpio *epg;
	int i;

	epg = devm_kzalloc(&pdev->dev, sizeof(*epg), GFP_KERNEL);
	if (!epg)
		return -ENOMEM;

	epg->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(epg->base))
		return PTR_ERR(epg->base);

	for (i = 0; i < ARRAY_SIZE(ep93xx_gpio_banks); i++) {
		struct gpio_chip *gc = &epg->gc[i];
		struct ep93xx_gpio_bank *bank = &ep93xx_gpio_banks[i];

		if (ep93xx_gpio_add_bank(gc, pdev, epg, bank))
			dev_warn(&pdev->dev, "Unable to add gpio bank %s\n",
				 bank->label);
	}

	return 0;
}