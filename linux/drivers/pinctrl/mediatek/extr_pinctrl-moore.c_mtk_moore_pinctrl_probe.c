#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct pinctrl_pin_desc {int /*<<< orphan*/  name; int /*<<< orphan*/  number; } ;
struct mtk_pinctrl {int nbase; int /*<<< orphan*/  pctrl; struct mtk_pin_soc const* soc; int /*<<< orphan*/ * base; TYPE_3__* dev; } ;
struct mtk_pin_soc {int nbase_names; int npins; TYPE_1__* pins; int /*<<< orphan*/ * base_names; } ;
struct TYPE_11__ {int npins; int /*<<< orphan*/  custom_conf_items; int /*<<< orphan*/  custom_params; int /*<<< orphan*/  num_custom_params; struct pinctrl_pin_desc const* pins; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 void* devm_kmalloc_array (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 struct mtk_pinctrl* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_pinctrl_register_and_init (TYPE_3__*,TYPE_2__*,struct mtk_pinctrl*,int /*<<< orphan*/ *) ; 
 int mtk_build_eint (struct mtk_pinctrl*,struct platform_device*) ; 
 int mtk_build_functions (struct mtk_pinctrl*) ; 
 int mtk_build_gpiochip (struct mtk_pinctrl*,int /*<<< orphan*/ ) ; 
 int mtk_build_groups (struct mtk_pinctrl*) ; 
 int /*<<< orphan*/  mtk_conf_items ; 
 int /*<<< orphan*/  mtk_custom_bindings ; 
 TYPE_2__ mtk_desc ; 
 int pinctrl_enable (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_pinctrl*) ; 

int mtk_moore_pinctrl_probe(struct platform_device *pdev,
			    const struct mtk_pin_soc *soc)
{
	struct pinctrl_pin_desc *pins;
	struct resource *res;
	struct mtk_pinctrl *hw;
	int err, i;

	hw = devm_kzalloc(&pdev->dev, sizeof(*hw), GFP_KERNEL);
	if (!hw)
		return -ENOMEM;

	hw->soc = soc;
	hw->dev = &pdev->dev;

	if (!hw->soc->nbase_names) {
		dev_err(&pdev->dev,
			"SoC should be assigned at least one register base\n");
		return -EINVAL;
	}

	hw->base = devm_kmalloc_array(&pdev->dev, hw->soc->nbase_names,
				      sizeof(*hw->base), GFP_KERNEL);
	if (!hw->base)
		return -ENOMEM;

	for (i = 0; i < hw->soc->nbase_names; i++) {
		res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
						   hw->soc->base_names[i]);
		if (!res) {
			dev_err(&pdev->dev, "missing IO resource\n");
			return -ENXIO;
		}

		hw->base[i] = devm_ioremap_resource(&pdev->dev, res);
		if (IS_ERR(hw->base[i]))
			return PTR_ERR(hw->base[i]);
	}

	hw->nbase = hw->soc->nbase_names;

	/* Copy from internal struct mtk_pin_desc to register to the core */
	pins = devm_kmalloc_array(&pdev->dev, hw->soc->npins, sizeof(*pins),
				  GFP_KERNEL);
	if (!pins)
		return -ENOMEM;

	for (i = 0; i < hw->soc->npins; i++) {
		pins[i].number = hw->soc->pins[i].number;
		pins[i].name = hw->soc->pins[i].name;
	}

	/* Setup pins descriptions per SoC types */
	mtk_desc.pins = (const struct pinctrl_pin_desc *)pins;
	mtk_desc.npins = hw->soc->npins;
	mtk_desc.num_custom_params = ARRAY_SIZE(mtk_custom_bindings);
	mtk_desc.custom_params = mtk_custom_bindings;
#ifdef CONFIG_DEBUG_FS
	mtk_desc.custom_conf_items = mtk_conf_items;
#endif

	err = devm_pinctrl_register_and_init(&pdev->dev, &mtk_desc, hw,
					     &hw->pctrl);
	if (err)
		return err;

	/* Setup groups descriptions per SoC types */
	err = mtk_build_groups(hw);
	if (err) {
		dev_err(&pdev->dev, "Failed to build groups\n");
		return err;
	}

	/* Setup functions descriptions per SoC types */
	err = mtk_build_functions(hw);
	if (err) {
		dev_err(&pdev->dev, "Failed to build functions\n");
		return err;
	}

	/* For able to make pinctrl_claim_hogs, we must not enable pinctrl
	 * until all groups and functions are being added one.
	 */
	err = pinctrl_enable(hw->pctrl);
	if (err)
		return err;

	err = mtk_build_eint(hw, pdev);
	if (err)
		dev_warn(&pdev->dev,
			 "Failed to add EINT, but pinctrl still can work\n");

	/* Build gpiochip should be after pinctrl_enable is done */
	err = mtk_build_gpiochip(hw, pdev->dev.of_node);
	if (err) {
		dev_err(&pdev->dev, "Failed to add gpio_chip\n");
		return err;
	}

	platform_set_drvdata(pdev, hw);

	return 0;
}