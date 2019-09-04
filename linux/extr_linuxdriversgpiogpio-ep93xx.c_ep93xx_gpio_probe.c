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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct gpio_chip {int dummy; } ;
struct ep93xx_gpio_bank {int /*<<< orphan*/  label; } ;
struct ep93xx_gpio {int /*<<< orphan*/  mmio_base; struct gpio_chip* gc; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ep93xx_gpio_bank*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct ep93xx_gpio* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ep93xx_gpio_add_bank (struct gpio_chip*,struct device*,int /*<<< orphan*/ ,struct ep93xx_gpio_bank*) ; 
 struct ep93xx_gpio_bank* ep93xx_gpio_banks ; 
 int /*<<< orphan*/  ep93xx_gpio_init_irq () ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ep93xx_gpio_probe(struct platform_device *pdev)
{
	struct ep93xx_gpio *ep93xx_gpio;
	struct resource *res;
	int i;
	struct device *dev = &pdev->dev;

	ep93xx_gpio = devm_kzalloc(dev, sizeof(struct ep93xx_gpio), GFP_KERNEL);
	if (!ep93xx_gpio)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ep93xx_gpio->mmio_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(ep93xx_gpio->mmio_base))
		return PTR_ERR(ep93xx_gpio->mmio_base);

	for (i = 0; i < ARRAY_SIZE(ep93xx_gpio_banks); i++) {
		struct gpio_chip *gc = &ep93xx_gpio->gc[i];
		struct ep93xx_gpio_bank *bank = &ep93xx_gpio_banks[i];

		if (ep93xx_gpio_add_bank(gc, &pdev->dev,
					 ep93xx_gpio->mmio_base, bank))
			dev_warn(&pdev->dev, "Unable to add gpio bank %s\n",
				bank->label);
	}

	ep93xx_gpio_init_irq();

	return 0;
}