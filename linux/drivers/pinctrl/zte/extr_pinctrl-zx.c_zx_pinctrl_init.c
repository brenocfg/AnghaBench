#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct zx_pinctrl_soc_info {int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; } ;
struct zx_pinctrl {int /*<<< orphan*/  pctldev; struct zx_pinctrl_soc_info* info; TYPE_1__* dev; int /*<<< orphan*/  aux_base; int /*<<< orphan*/  base; int /*<<< orphan*/  lock; } ;
struct resource {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct pinctrl_desc {int /*<<< orphan*/ * confops; int /*<<< orphan*/ * pmxops; int /*<<< orphan*/ * pctlops; int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 void* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (TYPE_1__*,struct pinctrl_desc*,struct zx_pinctrl*) ; 
 int /*<<< orphan*/  of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct zx_pinctrl*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zx_pinconf_ops ; 
 int zx_pinctrl_build_state (struct platform_device*) ; 
 int /*<<< orphan*/  zx_pinctrl_ops ; 
 int /*<<< orphan*/  zx_pinmux_ops ; 

int zx_pinctrl_init(struct platform_device *pdev,
		    struct zx_pinctrl_soc_info *info)
{
	struct pinctrl_desc *pctldesc;
	struct zx_pinctrl *zpctl;
	struct device_node *np;
	struct resource *res;
	int ret;

	zpctl = devm_kzalloc(&pdev->dev, sizeof(*zpctl), GFP_KERNEL);
	if (!zpctl)
		return -ENOMEM;

	spin_lock_init(&zpctl->lock);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	zpctl->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(zpctl->base))
		return PTR_ERR(zpctl->base);

	np = of_parse_phandle(pdev->dev.of_node, "zte,auxiliary-controller", 0);
	if (!np) {
		dev_err(&pdev->dev, "failed to find auxiliary controller\n");
		return -ENODEV;
	}

	zpctl->aux_base = of_iomap(np, 0);
	of_node_put(np);
	if (!zpctl->aux_base)
		return -ENOMEM;

	zpctl->dev = &pdev->dev;
	zpctl->info = info;

	pctldesc = devm_kzalloc(&pdev->dev, sizeof(*pctldesc), GFP_KERNEL);
	if (!pctldesc)
		return -ENOMEM;

	pctldesc->name = dev_name(&pdev->dev);
	pctldesc->owner = THIS_MODULE;
	pctldesc->pins = info->pins;
	pctldesc->npins = info->npins;
	pctldesc->pctlops = &zx_pinctrl_ops;
	pctldesc->pmxops = &zx_pinmux_ops;
	pctldesc->confops = &zx_pinconf_ops;

	zpctl->pctldev = devm_pinctrl_register(&pdev->dev, pctldesc, zpctl);
	if (IS_ERR(zpctl->pctldev)) {
		ret = PTR_ERR(zpctl->pctldev);
		dev_err(&pdev->dev, "failed to register pinctrl: %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, zpctl);

	ret = zx_pinctrl_build_state(pdev);
	if (ret) {
		dev_err(&pdev->dev, "failed to build state: %d\n", ret);
		return ret;
	}

	dev_info(&pdev->dev, "initialized pinctrl driver\n");
	return 0;
}