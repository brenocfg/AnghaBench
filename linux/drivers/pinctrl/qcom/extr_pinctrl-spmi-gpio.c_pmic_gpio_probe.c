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
typedef  scalar_t__ u32 ;
struct TYPE_6__ {int /*<<< orphan*/  translate; } ;
struct gpio_irq_chip {TYPE_1__ child_irq_domain_ops; int /*<<< orphan*/  child_offset_to_irq; int /*<<< orphan*/  populate_parent_fwspec; int /*<<< orphan*/  child_to_parent_hwirq; struct irq_domain* parent_domain; int /*<<< orphan*/  fwnode; int /*<<< orphan*/  handler; int /*<<< orphan*/  default_type; int /*<<< orphan*/ * chip; } ;
struct TYPE_7__ {int base; int ngpio; int of_gpio_n_cells; int can_sleep; struct gpio_irq_chip irq; void* label; struct device* parent; } ;
struct pmic_gpio_state {TYPE_2__ chip; struct device* dev; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  map; } ;
struct pmic_gpio_pad {scalar_t__ base; } ;
struct device {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct pinctrl_pin_desc {int number; int /*<<< orphan*/  name; struct pmic_gpio_pad* drv_data; } ;
struct pinctrl_desc {int npins; int /*<<< orphan*/  custom_conf_items; int /*<<< orphan*/  custom_params; int /*<<< orphan*/  num_custom_params; struct pinctrl_pin_desc* pins; void* name; int /*<<< orphan*/  owner; int /*<<< orphan*/ * confops; int /*<<< orphan*/ * pmxops; int /*<<< orphan*/ * pctlops; } ;
struct irq_domain {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PMIC_GPIO_ADDRESS_RANGE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* dev_name (struct device*) ; 
 scalar_t__ device_get_match_data (struct device*) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (struct device*,struct pinctrl_desc*,struct pmic_gpio_state*) ; 
 int gpiochip_add_data (TYPE_2__*,struct pmic_gpio_state*) ; 
 int gpiochip_add_pin_range (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpiochip_populate_parent_fwspec_fourcell ; 
 int /*<<< orphan*/  gpiochip_remove (TYPE_2__*) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 struct irq_domain* irq_find_host (struct device_node*) ; 
 struct device_node* of_irq_find_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_node_to_fwnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pmic_gpio_state*) ; 
 int /*<<< orphan*/  pmic_conf_items ; 
 int /*<<< orphan*/  pmic_gpio_bindings ; 
 int /*<<< orphan*/  pmic_gpio_child_offset_to_irq ; 
 int /*<<< orphan*/  pmic_gpio_child_to_parent_hwirq ; 
 int /*<<< orphan*/  pmic_gpio_domain_translate ; 
 TYPE_2__ pmic_gpio_gpio_template ; 
 int /*<<< orphan*/ * pmic_gpio_groups ; 
 int /*<<< orphan*/  pmic_gpio_irq_chip ; 
 int /*<<< orphan*/  pmic_gpio_pinconf_ops ; 
 int /*<<< orphan*/  pmic_gpio_pinctrl_ops ; 
 int /*<<< orphan*/  pmic_gpio_pinmux_ops ; 
 int pmic_gpio_populate (struct pmic_gpio_state*,struct pmic_gpio_pad*) ; 

__attribute__((used)) static int pmic_gpio_probe(struct platform_device *pdev)
{
	struct irq_domain *parent_domain;
	struct device_node *parent_node;
	struct device *dev = &pdev->dev;
	struct pinctrl_pin_desc *pindesc;
	struct pinctrl_desc *pctrldesc;
	struct pmic_gpio_pad *pad, *pads;
	struct pmic_gpio_state *state;
	struct gpio_irq_chip *girq;
	int ret, npins, i;
	u32 reg;

	ret = of_property_read_u32(dev->of_node, "reg", &reg);
	if (ret < 0) {
		dev_err(dev, "missing base address");
		return ret;
	}

	npins = (uintptr_t) device_get_match_data(&pdev->dev);

	state = devm_kzalloc(dev, sizeof(*state), GFP_KERNEL);
	if (!state)
		return -ENOMEM;

	platform_set_drvdata(pdev, state);

	state->dev = &pdev->dev;
	state->map = dev_get_regmap(dev->parent, NULL);

	pindesc = devm_kcalloc(dev, npins, sizeof(*pindesc), GFP_KERNEL);
	if (!pindesc)
		return -ENOMEM;

	pads = devm_kcalloc(dev, npins, sizeof(*pads), GFP_KERNEL);
	if (!pads)
		return -ENOMEM;

	pctrldesc = devm_kzalloc(dev, sizeof(*pctrldesc), GFP_KERNEL);
	if (!pctrldesc)
		return -ENOMEM;

	pctrldesc->pctlops = &pmic_gpio_pinctrl_ops;
	pctrldesc->pmxops = &pmic_gpio_pinmux_ops;
	pctrldesc->confops = &pmic_gpio_pinconf_ops;
	pctrldesc->owner = THIS_MODULE;
	pctrldesc->name = dev_name(dev);
	pctrldesc->pins = pindesc;
	pctrldesc->npins = npins;
	pctrldesc->num_custom_params = ARRAY_SIZE(pmic_gpio_bindings);
	pctrldesc->custom_params = pmic_gpio_bindings;
#ifdef CONFIG_DEBUG_FS
	pctrldesc->custom_conf_items = pmic_conf_items;
#endif

	for (i = 0; i < npins; i++, pindesc++) {
		pad = &pads[i];
		pindesc->drv_data = pad;
		pindesc->number = i;
		pindesc->name = pmic_gpio_groups[i];

		pad->base = reg + i * PMIC_GPIO_ADDRESS_RANGE;

		ret = pmic_gpio_populate(state, pad);
		if (ret < 0)
			return ret;
	}

	state->chip = pmic_gpio_gpio_template;
	state->chip.parent = dev;
	state->chip.base = -1;
	state->chip.ngpio = npins;
	state->chip.label = dev_name(dev);
	state->chip.of_gpio_n_cells = 2;
	state->chip.can_sleep = false;

	state->ctrl = devm_pinctrl_register(dev, pctrldesc, state);
	if (IS_ERR(state->ctrl))
		return PTR_ERR(state->ctrl);

	parent_node = of_irq_find_parent(state->dev->of_node);
	if (!parent_node)
		return -ENXIO;

	parent_domain = irq_find_host(parent_node);
	of_node_put(parent_node);
	if (!parent_domain)
		return -ENXIO;

	girq = &state->chip.irq;
	girq->chip = &pmic_gpio_irq_chip;
	girq->default_type = IRQ_TYPE_NONE;
	girq->handler = handle_level_irq;
	girq->fwnode = of_node_to_fwnode(state->dev->of_node);
	girq->parent_domain = parent_domain;
	girq->child_to_parent_hwirq = pmic_gpio_child_to_parent_hwirq;
	girq->populate_parent_fwspec = gpiochip_populate_parent_fwspec_fourcell;
	girq->child_offset_to_irq = pmic_gpio_child_offset_to_irq;
	girq->child_irq_domain_ops.translate = pmic_gpio_domain_translate;

	ret = gpiochip_add_data(&state->chip, state);
	if (ret) {
		dev_err(state->dev, "can't add gpio chip\n");
		return ret;
	}

	/*
	 * For DeviceTree-supported systems, the gpio core checks the
	 * pinctrl's device node for the "gpio-ranges" property.
	 * If it is present, it takes care of adding the pin ranges
	 * for the driver. In this case the driver can skip ahead.
	 *
	 * In order to remain compatible with older, existing DeviceTree
	 * files which don't set the "gpio-ranges" property or systems that
	 * utilize ACPI the driver has to call gpiochip_add_pin_range().
	 */
	if (!of_property_read_bool(dev->of_node, "gpio-ranges")) {
		ret = gpiochip_add_pin_range(&state->chip, dev_name(dev), 0, 0,
					     npins);
		if (ret) {
			dev_err(dev, "failed to add pin range\n");
			goto err_range;
		}
	}

	return 0;

err_range:
	gpiochip_remove(&state->chip);
	return ret;
}