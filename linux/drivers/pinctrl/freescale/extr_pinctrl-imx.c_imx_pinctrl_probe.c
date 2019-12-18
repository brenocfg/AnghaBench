#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct regmap_config {char* name; } ;
struct regmap {int dummy; } ;
struct TYPE_10__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct pinctrl_desc {int npins; int /*<<< orphan*/  num_custom_params; int /*<<< orphan*/  custom_params; int /*<<< orphan*/  owner; int /*<<< orphan*/ * confops; TYPE_2__* pmxops; int /*<<< orphan*/ * pctlops; scalar_t__ pins; int /*<<< orphan*/  name; } ;
struct imx_pinctrl_soc_info {int npins; int flags; int /*<<< orphan*/  gpio_set_direction; int /*<<< orphan*/  num_custom_params; int /*<<< orphan*/  custom_params; scalar_t__ pins; scalar_t__ gpr_compatible; } ;
struct imx_pinctrl {int /*<<< orphan*/  pctl; TYPE_1__* dev; struct imx_pinctrl_soc_info const* info; int /*<<< orphan*/  mutex; int /*<<< orphan*/  input_sel_base; struct regmap* base; TYPE_5__* pin_regs; } ;
struct device_node {int dummy; } ;
struct TYPE_12__ {int mux_reg; int conf_reg; } ;
struct TYPE_11__ {int /*<<< orphan*/  gpio_set_direction; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IMX_USE_SCU ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 TYPE_5__* devm_kmalloc_array (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_pinctrl_register_and_init (TYPE_1__*,struct pinctrl_desc*,struct imx_pinctrl*,int /*<<< orphan*/ *) ; 
 struct regmap* devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_free_resources (struct imx_pinctrl*) ; 
 int /*<<< orphan*/  imx_pctrl_ops ; 
 int /*<<< orphan*/  imx_pinconf_ops ; 
 int imx_pinctrl_probe_dt (struct platform_device*,struct imx_pinctrl*) ; 
 TYPE_2__ imx_pmx_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int pinctrl_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct imx_pinctrl*) ; 
 int /*<<< orphan*/  regmap_attach_dev (TYPE_1__*,struct regmap*,struct regmap_config*) ; 
 struct regmap* syscon_regmap_lookup_by_compatible (scalar_t__) ; 

int imx_pinctrl_probe(struct platform_device *pdev,
		      const struct imx_pinctrl_soc_info *info)
{
	struct regmap_config config = { .name = "gpr" };
	struct device_node *dev_np = pdev->dev.of_node;
	struct pinctrl_desc *imx_pinctrl_desc;
	struct device_node *np;
	struct imx_pinctrl *ipctl;
	struct regmap *gpr;
	int ret, i;

	if (!info || !info->pins || !info->npins) {
		dev_err(&pdev->dev, "wrong pinctrl info\n");
		return -EINVAL;
	}

	if (info->gpr_compatible) {
		gpr = syscon_regmap_lookup_by_compatible(info->gpr_compatible);
		if (!IS_ERR(gpr))
			regmap_attach_dev(&pdev->dev, gpr, &config);
	}

	/* Create state holders etc for this driver */
	ipctl = devm_kzalloc(&pdev->dev, sizeof(*ipctl), GFP_KERNEL);
	if (!ipctl)
		return -ENOMEM;

	if (!(info->flags & IMX_USE_SCU)) {
		ipctl->pin_regs = devm_kmalloc_array(&pdev->dev, info->npins,
						     sizeof(*ipctl->pin_regs),
						     GFP_KERNEL);
		if (!ipctl->pin_regs)
			return -ENOMEM;

		for (i = 0; i < info->npins; i++) {
			ipctl->pin_regs[i].mux_reg = -1;
			ipctl->pin_regs[i].conf_reg = -1;
		}

		ipctl->base = devm_platform_ioremap_resource(pdev, 0);
		if (IS_ERR(ipctl->base))
			return PTR_ERR(ipctl->base);

		if (of_property_read_bool(dev_np, "fsl,input-sel")) {
			np = of_parse_phandle(dev_np, "fsl,input-sel", 0);
			if (!np) {
				dev_err(&pdev->dev, "iomuxc fsl,input-sel property not found\n");
				return -EINVAL;
			}

			ipctl->input_sel_base = of_iomap(np, 0);
			of_node_put(np);
			if (!ipctl->input_sel_base) {
				dev_err(&pdev->dev,
					"iomuxc input select base address not found\n");
				return -ENOMEM;
			}
		}
	}

	imx_pinctrl_desc = devm_kzalloc(&pdev->dev, sizeof(*imx_pinctrl_desc),
					GFP_KERNEL);
	if (!imx_pinctrl_desc)
		return -ENOMEM;

	imx_pinctrl_desc->name = dev_name(&pdev->dev);
	imx_pinctrl_desc->pins = info->pins;
	imx_pinctrl_desc->npins = info->npins;
	imx_pinctrl_desc->pctlops = &imx_pctrl_ops;
	imx_pinctrl_desc->pmxops = &imx_pmx_ops;
	imx_pinctrl_desc->confops = &imx_pinconf_ops;
	imx_pinctrl_desc->owner = THIS_MODULE;

	/* for generic pinconf */
	imx_pinctrl_desc->custom_params = info->custom_params;
	imx_pinctrl_desc->num_custom_params = info->num_custom_params;

	/* platform specific callback */
	imx_pmx_ops.gpio_set_direction = info->gpio_set_direction;

	mutex_init(&ipctl->mutex);

	ipctl->info = info;
	ipctl->dev = &pdev->dev;
	platform_set_drvdata(pdev, ipctl);
	ret = devm_pinctrl_register_and_init(&pdev->dev,
					     imx_pinctrl_desc, ipctl,
					     &ipctl->pctl);
	if (ret) {
		dev_err(&pdev->dev, "could not register IMX pinctrl driver\n");
		goto free;
	}

	ret = imx_pinctrl_probe_dt(pdev, ipctl);
	if (ret) {
		dev_err(&pdev->dev, "fail to probe dt properties\n");
		goto free;
	}

	dev_info(&pdev->dev, "initialized IMX pinctrl driver\n");

	return pinctrl_enable(ipctl->pctl);

free:
	imx_free_resources(ipctl);

	return ret;
}