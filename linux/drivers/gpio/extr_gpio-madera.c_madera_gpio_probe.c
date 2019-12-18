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
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct madera_pdata {int gpio_base; } ;
struct TYPE_8__ {int base; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  parent; } ;
struct madera_gpio {TYPE_1__ gpio_chip; struct madera* madera; } ;
struct madera {int type; struct madera_pdata pdata; } ;

/* Variables and functions */
#define  CS42L92 136 
#define  CS47L15 135 
 int /*<<< orphan*/  CS47L15_NUM_GPIOS ; 
#define  CS47L35 134 
 int /*<<< orphan*/  CS47L35_NUM_GPIOS ; 
#define  CS47L85 133 
 int /*<<< orphan*/  CS47L85_NUM_GPIOS ; 
#define  CS47L90 132 
 int /*<<< orphan*/  CS47L90_NUM_GPIOS ; 
#define  CS47L91 131 
#define  CS47L92 130 
 int /*<<< orphan*/  CS47L92_NUM_GPIOS ; 
#define  CS47L93 129 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  WM1840 128 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 struct madera* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int devm_gpiochip_add_data (TYPE_3__*,TYPE_1__*,struct madera_gpio*) ; 
 struct madera_gpio* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int gpiochip_add_pin_range (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ madera_gpio_chip ; 

__attribute__((used)) static int madera_gpio_probe(struct platform_device *pdev)
{
	struct madera *madera = dev_get_drvdata(pdev->dev.parent);
	struct madera_pdata *pdata = &madera->pdata;
	struct madera_gpio *madera_gpio;
	int ret;

	madera_gpio = devm_kzalloc(&pdev->dev, sizeof(*madera_gpio),
				   GFP_KERNEL);
	if (!madera_gpio)
		return -ENOMEM;

	madera_gpio->madera = madera;

	/* Construct suitable gpio_chip from the template in madera_gpio_chip */
	madera_gpio->gpio_chip = madera_gpio_chip;
	madera_gpio->gpio_chip.parent = pdev->dev.parent;

	switch (madera->type) {
	case CS47L15:
		madera_gpio->gpio_chip.ngpio = CS47L15_NUM_GPIOS;
		break;
	case CS47L35:
		madera_gpio->gpio_chip.ngpio = CS47L35_NUM_GPIOS;
		break;
	case CS47L85:
	case WM1840:
		madera_gpio->gpio_chip.ngpio = CS47L85_NUM_GPIOS;
		break;
	case CS47L90:
	case CS47L91:
		madera_gpio->gpio_chip.ngpio = CS47L90_NUM_GPIOS;
		break;
	case CS42L92:
	case CS47L92:
	case CS47L93:
		madera_gpio->gpio_chip.ngpio = CS47L92_NUM_GPIOS;
		break;
	default:
		dev_err(&pdev->dev, "Unknown chip variant %d\n", madera->type);
		return -EINVAL;
	}

	/* We want to be usable on systems that don't use devicetree or acpi */
	if (pdata->gpio_base)
		madera_gpio->gpio_chip.base = pdata->gpio_base;
	else
		madera_gpio->gpio_chip.base = -1;

	ret = devm_gpiochip_add_data(&pdev->dev,
				     &madera_gpio->gpio_chip,
				     madera_gpio);
	if (ret < 0) {
		dev_dbg(&pdev->dev, "Could not register gpiochip, %d\n", ret);
		return ret;
	}

	/*
	 * This is part of a composite MFD device which can only be used with
	 * the corresponding pinctrl driver. On all supported silicon the GPIO
	 * to pinctrl mapping is fixed in the silicon, so we register it
	 * explicitly instead of requiring a redundant gpio-ranges in the
	 * devicetree.
	 * In any case we also want to work on systems that don't use devicetree
	 * or acpi.
	 */
	ret = gpiochip_add_pin_range(&madera_gpio->gpio_chip, "madera-pinctrl",
				     0, 0, madera_gpio->gpio_chip.ngpio);
	if (ret) {
		dev_dbg(&pdev->dev, "Failed to add pin range (%d)\n", ret);
		return ret;
	}

	return 0;
}