#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct resource {int dummy; } ;
struct TYPE_11__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct pinctrl_gpio_range {int id; int pin_base; int base; int npins; struct gpio_chip* gc; int /*<<< orphan*/  name; } ;
struct gpio_chip {int base; int ngpio; char const* const* names; int /*<<< orphan*/  label; int /*<<< orphan*/  owner; TYPE_2__* parent; struct device_node* of_node; } ;
struct device_node {int dummy; } ;
struct at91_pinctrl_mux_ops {int dummy; } ;
struct at91_gpio_chip {int pioc_virq; int pioc_idx; int /*<<< orphan*/  clock; int /*<<< orphan*/  regbase; struct pinctrl_gpio_range range; struct gpio_chip chip; struct at91_pinctrl_mux_ops* ops; } ;
struct TYPE_10__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct at91_gpio_chip**) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX_NB_GPIO_PER_BANK ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int at91_gpio_of_irq_setup (struct platform_device*,struct at91_gpio_chip*) ; 
 int /*<<< orphan*/  at91_gpio_of_match ; 
 struct gpio_chip at91_gpio_template ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 char** devm_kcalloc (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 struct at91_gpio_chip* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_banks ; 
 struct at91_gpio_chip** gpio_chips ; 
 int gpiochip_add_data (struct gpio_chip*,struct at91_gpio_chip*) ; 
 int /*<<< orphan*/  gpiochip_remove (struct gpio_chip*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 TYPE_1__* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int) ; 

__attribute__((used)) static int at91_gpio_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct resource *res;
	struct at91_gpio_chip *at91_chip = NULL;
	struct gpio_chip *chip;
	struct pinctrl_gpio_range *range;
	int ret = 0;
	int irq, i;
	int alias_idx = of_alias_get_id(np, "gpio");
	uint32_t ngpio;
	char **names;

	BUG_ON(alias_idx >= ARRAY_SIZE(gpio_chips));
	if (gpio_chips[alias_idx]) {
		ret = -EBUSY;
		goto err;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		ret = irq;
		goto err;
	}

	at91_chip = devm_kzalloc(&pdev->dev, sizeof(*at91_chip), GFP_KERNEL);
	if (!at91_chip) {
		ret = -ENOMEM;
		goto err;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	at91_chip->regbase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(at91_chip->regbase)) {
		ret = PTR_ERR(at91_chip->regbase);
		goto err;
	}

	at91_chip->ops = (struct at91_pinctrl_mux_ops *)
		of_match_device(at91_gpio_of_match, &pdev->dev)->data;
	at91_chip->pioc_virq = irq;
	at91_chip->pioc_idx = alias_idx;

	at91_chip->clock = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(at91_chip->clock)) {
		dev_err(&pdev->dev, "failed to get clock, ignoring.\n");
		ret = PTR_ERR(at91_chip->clock);
		goto err;
	}

	ret = clk_prepare_enable(at91_chip->clock);
	if (ret) {
		dev_err(&pdev->dev, "failed to prepare and enable clock, ignoring.\n");
		goto clk_enable_err;
	}

	at91_chip->chip = at91_gpio_template;

	chip = &at91_chip->chip;
	chip->of_node = np;
	chip->label = dev_name(&pdev->dev);
	chip->parent = &pdev->dev;
	chip->owner = THIS_MODULE;
	chip->base = alias_idx * MAX_NB_GPIO_PER_BANK;

	if (!of_property_read_u32(np, "#gpio-lines", &ngpio)) {
		if (ngpio >= MAX_NB_GPIO_PER_BANK)
			pr_err("at91_gpio.%d, gpio-nb >= %d failback to %d\n",
			       alias_idx, MAX_NB_GPIO_PER_BANK, MAX_NB_GPIO_PER_BANK);
		else
			chip->ngpio = ngpio;
	}

	names = devm_kcalloc(&pdev->dev, chip->ngpio, sizeof(char *),
			     GFP_KERNEL);

	if (!names) {
		ret = -ENOMEM;
		goto clk_enable_err;
	}

	for (i = 0; i < chip->ngpio; i++)
		names[i] = kasprintf(GFP_KERNEL, "pio%c%d", alias_idx + 'A', i);

	chip->names = (const char *const *)names;

	range = &at91_chip->range;
	range->name = chip->label;
	range->id = alias_idx;
	range->pin_base = range->base = range->id * MAX_NB_GPIO_PER_BANK;

	range->npins = chip->ngpio;
	range->gc = chip;

	ret = gpiochip_add_data(chip, at91_chip);
	if (ret)
		goto gpiochip_add_err;

	gpio_chips[alias_idx] = at91_chip;
	gpio_banks = max(gpio_banks, alias_idx + 1);

	ret = at91_gpio_of_irq_setup(pdev, at91_chip);
	if (ret)
		goto irq_setup_err;

	dev_info(&pdev->dev, "at address %p\n", at91_chip->regbase);

	return 0;

irq_setup_err:
	gpiochip_remove(chip);
gpiochip_add_err:
clk_enable_err:
	clk_disable_unprepare(at91_chip->clock);
err:
	dev_err(&pdev->dev, "Failure %i for GPIO %i\n", ret, alias_idx);

	return ret;
}