#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct pm8xxx_pin_data {scalar_t__ irq; int /*<<< orphan*/  reg; } ;
struct TYPE_14__ {int base; int of_gpio_n_cells; int ngpio; int /*<<< orphan*/  label; int /*<<< orphan*/  of_node; TYPE_6__* parent; } ;
struct TYPE_13__ {int npins; int /*<<< orphan*/  custom_conf_items; int /*<<< orphan*/  custom_params; int /*<<< orphan*/  num_custom_params; struct pinctrl_pin_desc* pins; } ;
struct pm8xxx_mpp {int npins; TYPE_2__ chip; TYPE_6__* dev; int /*<<< orphan*/  pctrl; TYPE_1__ desc; int /*<<< orphan*/  regmap; } ;
struct TYPE_15__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_6__ dev; } ;
struct pinctrl_pin_desc {int number; struct pm8xxx_pin_data* drv_data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSBI_REG_ADDR_MPP (int) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (TYPE_6__*) ; 
 void* devm_kcalloc (TYPE_6__*,int,int,int /*<<< orphan*/ ) ; 
 struct pm8xxx_mpp* devm_kzalloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (TYPE_6__*,TYPE_1__*,struct pm8xxx_mpp*) ; 
 int gpiochip_add_data (TYPE_2__*,struct pm8xxx_mpp*) ; 
 int gpiochip_add_pin_range (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpiochip_remove (TYPE_2__*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int) ; 
 int platform_irq_count (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pm8xxx_mpp*) ; 
 int /*<<< orphan*/  pm8xxx_conf_items ; 
 int /*<<< orphan*/ * pm8xxx_groups ; 
 int /*<<< orphan*/  pm8xxx_mpp_bindings ; 
 TYPE_2__ pm8xxx_mpp_template ; 
 int pm8xxx_pin_populate (struct pm8xxx_mpp*,struct pm8xxx_pin_data*) ; 
 TYPE_1__ pm8xxx_pinctrl_desc ; 

__attribute__((used)) static int pm8xxx_mpp_probe(struct platform_device *pdev)
{
	struct pm8xxx_pin_data *pin_data;
	struct pinctrl_pin_desc *pins;
	struct pm8xxx_mpp *pctrl;
	int ret;
	int i, npins;

	pctrl = devm_kzalloc(&pdev->dev, sizeof(*pctrl), GFP_KERNEL);
	if (!pctrl)
		return -ENOMEM;

	pctrl->dev = &pdev->dev;
	npins = platform_irq_count(pdev);
	if (!npins)
		return -EINVAL;
	if (npins < 0)
		return npins;
	pctrl->npins = npins;

	pctrl->regmap = dev_get_regmap(pdev->dev.parent, NULL);
	if (!pctrl->regmap) {
		dev_err(&pdev->dev, "parent regmap unavailable\n");
		return -ENXIO;
	}

	pctrl->desc = pm8xxx_pinctrl_desc;
	pctrl->desc.npins = pctrl->npins;

	pins = devm_kcalloc(&pdev->dev,
			    pctrl->desc.npins,
			    sizeof(struct pinctrl_pin_desc),
			    GFP_KERNEL);
	if (!pins)
		return -ENOMEM;

	pin_data = devm_kcalloc(&pdev->dev,
				pctrl->desc.npins,
				sizeof(struct pm8xxx_pin_data),
				GFP_KERNEL);
	if (!pin_data)
		return -ENOMEM;

	for (i = 0; i < pctrl->desc.npins; i++) {
		pin_data[i].reg = SSBI_REG_ADDR_MPP(i);
		pin_data[i].irq = platform_get_irq(pdev, i);
		if (pin_data[i].irq < 0)
			return pin_data[i].irq;

		ret = pm8xxx_pin_populate(pctrl, &pin_data[i]);
		if (ret)
			return ret;

		pins[i].number = i;
		pins[i].name = pm8xxx_groups[i];
		pins[i].drv_data = &pin_data[i];
	}
	pctrl->desc.pins = pins;

	pctrl->desc.num_custom_params = ARRAY_SIZE(pm8xxx_mpp_bindings);
	pctrl->desc.custom_params = pm8xxx_mpp_bindings;
#ifdef CONFIG_DEBUG_FS
	pctrl->desc.custom_conf_items = pm8xxx_conf_items;
#endif

	pctrl->pctrl = devm_pinctrl_register(&pdev->dev, &pctrl->desc, pctrl);
	if (IS_ERR(pctrl->pctrl)) {
		dev_err(&pdev->dev, "couldn't register pm8xxx mpp driver\n");
		return PTR_ERR(pctrl->pctrl);
	}

	pctrl->chip = pm8xxx_mpp_template;
	pctrl->chip.base = -1;
	pctrl->chip.parent = &pdev->dev;
	pctrl->chip.of_node = pdev->dev.of_node;
	pctrl->chip.of_gpio_n_cells = 2;
	pctrl->chip.label = dev_name(pctrl->dev);
	pctrl->chip.ngpio = pctrl->npins;
	ret = gpiochip_add_data(&pctrl->chip, pctrl);
	if (ret) {
		dev_err(&pdev->dev, "failed register gpiochip\n");
		return ret;
	}

	ret = gpiochip_add_pin_range(&pctrl->chip,
				     dev_name(pctrl->dev),
				     0, 0, pctrl->chip.ngpio);
	if (ret) {
		dev_err(pctrl->dev, "failed to add pin range\n");
		goto unregister_gpiochip;
	}

	platform_set_drvdata(pdev, pctrl);

	dev_dbg(&pdev->dev, "Qualcomm pm8xxx mpp driver probed\n");

	return 0;

unregister_gpiochip:
	gpiochip_remove(&pctrl->chip);

	return ret;
}