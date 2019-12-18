#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_8__ {struct device_node* of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct mtk_pinctrl {TYPE_2__* eint; TYPE_1__* soc; int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * gpio_xlate; struct mtk_pinctrl* pctl; scalar_t__ hw; TYPE_4__* dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  base; } ;
struct TYPE_6__ {scalar_t__ eint_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_EINT_MTK ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_4__*,struct resource*) ; 
 TYPE_2__* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int mtk_eint_do_init (TYPE_2__*) ; 
 int /*<<< orphan*/  mtk_eint_xt ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 

int mtk_build_eint(struct mtk_pinctrl *hw, struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct resource *res;

	if (!IS_ENABLED(CONFIG_EINT_MTK))
		return 0;

	if (!of_property_read_bool(np, "interrupt-controller"))
		return -ENODEV;

	hw->eint = devm_kzalloc(hw->dev, sizeof(*hw->eint), GFP_KERNEL);
	if (!hw->eint)
		return -ENOMEM;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "eint");
	if (!res) {
		dev_err(&pdev->dev, "Unable to get eint resource\n");
		return -ENODEV;
	}

	hw->eint->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(hw->eint->base))
		return PTR_ERR(hw->eint->base);

	hw->eint->irq = irq_of_parse_and_map(np, 0);
	if (!hw->eint->irq)
		return -EINVAL;

	if (!hw->soc->eint_hw)
		return -ENODEV;

	hw->eint->dev = &pdev->dev;
	hw->eint->hw = hw->soc->eint_hw;
	hw->eint->pctl = hw;
	hw->eint->gpio_xlate = &mtk_eint_xt;

	return mtk_eint_do_init(hw->eint);
}