#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  parent; struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct device_node {int dummy; } ;
struct abx500_pinrange {int /*<<< orphan*/  npins; scalar_t__ offset; } ;
struct TYPE_18__ {int base; int /*<<< orphan*/  ngpio; TYPE_1__* parent; } ;
struct abx500_pinctrl {TYPE_2__ chip; TYPE_13__* soc; int /*<<< orphan*/  pctldev; int /*<<< orphan*/  irq_cluster_size; int /*<<< orphan*/  irq_cluster; int /*<<< orphan*/  parent; TYPE_1__* dev; } ;
struct TYPE_19__ {int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; } ;
struct TYPE_16__ {int gpio_num_ranges; struct abx500_pinrange* gpio_ranges; int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; int /*<<< orphan*/  ngpio_irq_cluster; int /*<<< orphan*/  gpio_irq_cluster; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
#define  PINCTRL_AB8500 129 
#define  PINCTRL_AB8505 128 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abx500_get_gpio_num (TYPE_13__*) ; 
 int /*<<< orphan*/  abx500_gpio_match ; 
 int /*<<< orphan*/  abx500_pinctrl_ab8500_init (TYPE_13__**) ; 
 int /*<<< orphan*/  abx500_pinctrl_ab8505_init (TYPE_13__**) ; 
 TYPE_6__ abx500_pinctrl_desc ; 
 TYPE_2__ abx500gpio_chip ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 struct abx500_pinctrl* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (TYPE_1__*,TYPE_6__*,struct abx500_pinctrl*) ; 
 int gpiochip_add_data (TYPE_2__*,struct abx500_pinctrl*) ; 
 int gpiochip_add_pin_range (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_remove (TYPE_2__*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct abx500_pinctrl*) ; 

__attribute__((used)) static int abx500_gpio_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	const struct of_device_id *match;
	struct abx500_pinctrl *pct;
	unsigned int id = -1;
	int ret;
	int i;

	if (!np) {
		dev_err(&pdev->dev, "gpio dt node missing\n");
		return -ENODEV;
	}

	pct = devm_kzalloc(&pdev->dev, sizeof(*pct), GFP_KERNEL);
	if (!pct)
		return -ENOMEM;

	pct->dev = &pdev->dev;
	pct->parent = dev_get_drvdata(pdev->dev.parent);
	pct->chip = abx500gpio_chip;
	pct->chip.parent = &pdev->dev;
	pct->chip.base = -1; /* Dynamic allocation */

	match = of_match_device(abx500_gpio_match, &pdev->dev);
	if (!match) {
		dev_err(&pdev->dev, "gpio dt not matching\n");
		return -ENODEV;
	}
	id = (unsigned long)match->data;

	/* Poke in other ASIC variants here */
	switch (id) {
	case PINCTRL_AB8500:
		abx500_pinctrl_ab8500_init(&pct->soc);
		break;
	case PINCTRL_AB8505:
		abx500_pinctrl_ab8505_init(&pct->soc);
		break;
	default:
		dev_err(&pdev->dev, "Unsupported pinctrl sub driver (%d)\n", id);
		return -EINVAL;
	}

	if (!pct->soc) {
		dev_err(&pdev->dev, "Invalid SOC data\n");
		return -EINVAL;
	}

	pct->chip.ngpio = abx500_get_gpio_num(pct->soc);
	pct->irq_cluster = pct->soc->gpio_irq_cluster;
	pct->irq_cluster_size = pct->soc->ngpio_irq_cluster;

	ret = gpiochip_add_data(&pct->chip, pct);
	if (ret) {
		dev_err(&pdev->dev, "unable to add gpiochip: %d\n", ret);
		return ret;
	}
	dev_info(&pdev->dev, "added gpiochip\n");

	abx500_pinctrl_desc.pins = pct->soc->pins;
	abx500_pinctrl_desc.npins = pct->soc->npins;
	pct->pctldev = devm_pinctrl_register(&pdev->dev, &abx500_pinctrl_desc,
					     pct);
	if (IS_ERR(pct->pctldev)) {
		dev_err(&pdev->dev,
			"could not register abx500 pinctrl driver\n");
		ret = PTR_ERR(pct->pctldev);
		goto out_rem_chip;
	}
	dev_info(&pdev->dev, "registered pin controller\n");

	/* We will handle a range of GPIO pins */
	for (i = 0; i < pct->soc->gpio_num_ranges; i++) {
		const struct abx500_pinrange *p = &pct->soc->gpio_ranges[i];

		ret = gpiochip_add_pin_range(&pct->chip,
					dev_name(&pdev->dev),
					p->offset - 1, p->offset, p->npins);
		if (ret < 0)
			goto out_rem_chip;
	}

	platform_set_drvdata(pdev, pct);
	dev_info(&pdev->dev, "initialized abx500 pinctrl driver\n");

	return 0;

out_rem_chip:
	gpiochip_remove(&pct->chip);
	return ret;
}