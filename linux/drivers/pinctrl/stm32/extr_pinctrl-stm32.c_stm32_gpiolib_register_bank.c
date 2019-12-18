#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stm32_pinctrl {size_t nbanks; int /*<<< orphan*/  domain; struct stm32_gpio_bank* banks; int /*<<< orphan*/  pctl_dev; struct device* dev; } ;
struct TYPE_3__ {int base; int ngpio; int /*<<< orphan*/  label; struct device* parent; struct device_node* of_node; } ;
struct pinctrl_gpio_range {int id; int pin_base; int base; int npins; TYPE_1__* gc; int /*<<< orphan*/  name; } ;
struct stm32_gpio_bank {int bank_nr; int bank_ioport_nr; TYPE_1__ gpio_chip; int /*<<< orphan*/  domain; int /*<<< orphan*/  fwnode; int /*<<< orphan*/  lock; struct pinctrl_gpio_range range; struct reset_control* clk; struct reset_control* base; } ;
struct resource {int dummy; } ;
struct reset_control {int dummy; } ;
struct of_phandle_args {int* args; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct reset_control*) ; 
 int PTR_ERR (struct reset_control*) ; 
 int /*<<< orphan*/  STM32_GPIO_IRQ_LINE ; 
 int STM32_GPIO_PINS_PER_BANK ; 
 int clk_prepare (struct reset_control*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct reset_control* devm_ioremap_resource (struct device*,struct resource*) ; 
 int gpiochip_add_data (TYPE_1__*,struct stm32_gpio_bank*) ; 
 int /*<<< orphan*/  irq_domain_create_hierarchy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct stm32_gpio_bank*) ; 
 scalar_t__ of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 struct reset_control* of_clk_get_by_name (struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_to_fwnode (struct device_node*) ; 
 int /*<<< orphan*/  of_parse_phandle_with_fixed_args (struct device_node*,char*,int,int /*<<< orphan*/ ,struct of_phandle_args*) ; 
 int /*<<< orphan*/  of_property_read_string (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 
 struct reset_control* of_reset_control_get_exclusive (struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pinctrl_add_gpio_range (int /*<<< orphan*/ ,struct pinctrl_gpio_range*) ; 
 int /*<<< orphan*/  reset_control_deassert (struct reset_control*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_gpio_domain_ops ; 
 TYPE_1__ stm32_gpio_template ; 

__attribute__((used)) static int stm32_gpiolib_register_bank(struct stm32_pinctrl *pctl,
	struct device_node *np)
{
	struct stm32_gpio_bank *bank = &pctl->banks[pctl->nbanks];
	int bank_ioport_nr;
	struct pinctrl_gpio_range *range = &bank->range;
	struct of_phandle_args args;
	struct device *dev = pctl->dev;
	struct resource res;
	struct reset_control *rstc;
	int npins = STM32_GPIO_PINS_PER_BANK;
	int bank_nr, err;

	rstc = of_reset_control_get_exclusive(np, NULL);
	if (!IS_ERR(rstc))
		reset_control_deassert(rstc);

	if (of_address_to_resource(np, 0, &res))
		return -ENODEV;

	bank->base = devm_ioremap_resource(dev, &res);
	if (IS_ERR(bank->base))
		return PTR_ERR(bank->base);

	bank->clk = of_clk_get_by_name(np, NULL);
	if (IS_ERR(bank->clk)) {
		dev_err(dev, "failed to get clk (%ld)\n", PTR_ERR(bank->clk));
		return PTR_ERR(bank->clk);
	}

	err = clk_prepare(bank->clk);
	if (err) {
		dev_err(dev, "failed to prepare clk (%d)\n", err);
		return err;
	}

	bank->gpio_chip = stm32_gpio_template;

	of_property_read_string(np, "st,bank-name", &bank->gpio_chip.label);

	if (!of_parse_phandle_with_fixed_args(np, "gpio-ranges", 3, 0, &args)) {
		bank_nr = args.args[1] / STM32_GPIO_PINS_PER_BANK;
		bank->gpio_chip.base = args.args[1];
	} else {
		bank_nr = pctl->nbanks;
		bank->gpio_chip.base = bank_nr * STM32_GPIO_PINS_PER_BANK;
		range->name = bank->gpio_chip.label;
		range->id = bank_nr;
		range->pin_base = range->id * STM32_GPIO_PINS_PER_BANK;
		range->base = range->id * STM32_GPIO_PINS_PER_BANK;
		range->npins = npins;
		range->gc = &bank->gpio_chip;
		pinctrl_add_gpio_range(pctl->pctl_dev,
				       &pctl->banks[bank_nr].range);
	}

	if (of_property_read_u32(np, "st,bank-ioport", &bank_ioport_nr))
		bank_ioport_nr = bank_nr;

	bank->gpio_chip.base = bank_nr * STM32_GPIO_PINS_PER_BANK;

	bank->gpio_chip.ngpio = npins;
	bank->gpio_chip.of_node = np;
	bank->gpio_chip.parent = dev;
	bank->bank_nr = bank_nr;
	bank->bank_ioport_nr = bank_ioport_nr;
	spin_lock_init(&bank->lock);

	/* create irq hierarchical domain */
	bank->fwnode = of_node_to_fwnode(np);

	bank->domain = irq_domain_create_hierarchy(pctl->domain, 0,
					STM32_GPIO_IRQ_LINE, bank->fwnode,
					&stm32_gpio_domain_ops, bank);

	if (!bank->domain)
		return -ENODEV;

	err = gpiochip_add_data(&bank->gpio_chip, bank);
	if (err) {
		dev_err(dev, "Failed to add gpiochip(%d)!\n", bank_nr);
		return err;
	}

	dev_info(dev, "%s bank added\n", bank->gpio_chip.label);
	return 0;
}