#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int base; int can_sleep; int /*<<< orphan*/  dbg_show; int /*<<< orphan*/  parent; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  set_config; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  label; } ;
struct wcove_gpio {int /*<<< orphan*/  regmap; TYPE_1__ chip; int /*<<< orphan*/  regmap_irq_chip; struct device* dev; int /*<<< orphan*/  buslock; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct intel_soc_pmic {int /*<<< orphan*/  regmap; int /*<<< orphan*/  irq_chip_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIO_IRQ0_MASK ; 
 int /*<<< orphan*/  GPIO_IRQ1_MASK ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IRQ_MASK_BASE ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  WCOVE_VGPIO_NUM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct intel_soc_pmic* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int devm_gpiochip_add_data (struct device*,TYPE_1__*,struct wcove_gpio*) ; 
 struct wcove_gpio* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wcove_gpio*) ; 
 int gpiochip_irqchip_add_nested (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_set_nested_irqchip (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct wcove_gpio*) ; 
 int regmap_irq_get_virq (int /*<<< orphan*/ ,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wcove_gpio_dbg_show ; 
 int /*<<< orphan*/  wcove_gpio_dir_in ; 
 int /*<<< orphan*/  wcove_gpio_dir_out ; 
 int /*<<< orphan*/  wcove_gpio_get ; 
 int /*<<< orphan*/  wcove_gpio_get_direction ; 
 int /*<<< orphan*/  wcove_gpio_irq_handler ; 
 int /*<<< orphan*/  wcove_gpio_set ; 
 int /*<<< orphan*/  wcove_gpio_set_config ; 
 int /*<<< orphan*/  wcove_irqchip ; 

__attribute__((used)) static int wcove_gpio_probe(struct platform_device *pdev)
{
	struct intel_soc_pmic *pmic;
	struct wcove_gpio *wg;
	int virq, ret, irq;
	struct device *dev;

	/*
	 * This gpio platform device is created by a mfd device (see
	 * drivers/mfd/intel_soc_pmic_bxtwc.c for details). Information
	 * shared by all sub-devices created by the mfd device, the regmap
	 * pointer for instance, is stored as driver data of the mfd device
	 * driver.
	 */
	pmic = dev_get_drvdata(pdev->dev.parent);
	if (!pmic)
		return -ENODEV;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	dev = &pdev->dev;

	wg = devm_kzalloc(dev, sizeof(*wg), GFP_KERNEL);
	if (!wg)
		return -ENOMEM;

	wg->regmap_irq_chip = pmic->irq_chip_data;

	platform_set_drvdata(pdev, wg);

	mutex_init(&wg->buslock);
	wg->chip.label = KBUILD_MODNAME;
	wg->chip.direction_input = wcove_gpio_dir_in;
	wg->chip.direction_output = wcove_gpio_dir_out;
	wg->chip.get_direction = wcove_gpio_get_direction;
	wg->chip.get = wcove_gpio_get;
	wg->chip.set = wcove_gpio_set;
	wg->chip.set_config = wcove_gpio_set_config,
	wg->chip.base = -1;
	wg->chip.ngpio = WCOVE_VGPIO_NUM;
	wg->chip.can_sleep = true;
	wg->chip.parent = pdev->dev.parent;
	wg->chip.dbg_show = wcove_gpio_dbg_show;
	wg->dev = dev;
	wg->regmap = pmic->regmap;

	ret = devm_gpiochip_add_data(dev, &wg->chip, wg);
	if (ret) {
		dev_err(dev, "Failed to add gpiochip: %d\n", ret);
		return ret;
	}

	ret = gpiochip_irqchip_add_nested(&wg->chip, &wcove_irqchip, 0,
					  handle_simple_irq, IRQ_TYPE_NONE);
	if (ret) {
		dev_err(dev, "Failed to add irqchip: %d\n", ret);
		return ret;
	}

	virq = regmap_irq_get_virq(wg->regmap_irq_chip, irq);
	if (virq < 0) {
		dev_err(dev, "Failed to get virq by irq %d\n", irq);
		return virq;
	}

	ret = devm_request_threaded_irq(dev, virq, NULL,
		wcove_gpio_irq_handler, IRQF_ONESHOT, pdev->name, wg);
	if (ret) {
		dev_err(dev, "Failed to request irq %d\n", virq);
		return ret;
	}

	gpiochip_set_nested_irqchip(&wg->chip, &wcove_irqchip, virq);

	/* Enable GPIO0 interrupts */
	ret = regmap_update_bits(wg->regmap, IRQ_MASK_BASE, GPIO_IRQ0_MASK,
				 0x00);
	if (ret)
		return ret;

	/* Enable GPIO1 interrupts */
	ret = regmap_update_bits(wg->regmap, IRQ_MASK_BASE + 1, GPIO_IRQ1_MASK,
				 0x00);
	if (ret)
		return ret;

	return 0;
}