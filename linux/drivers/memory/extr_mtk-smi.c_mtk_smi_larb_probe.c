#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_3__ {struct device* dev; int /*<<< orphan*/ * clk_gals0; int /*<<< orphan*/ * clk_smi; int /*<<< orphan*/ * clk_apb; } ;
struct mtk_smi_larb {struct device* smi_common_dev; TYPE_1__ smi; TYPE_2__* larb_gen; int /*<<< orphan*/ * base; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {scalar_t__ has_gals; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int component_add (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (struct device*,struct resource*) ; 
 struct mtk_smi_larb* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_smi_larb_component_ops ; 
 TYPE_2__* of_device_get_match_data (struct device*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_smi_larb*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 

__attribute__((used)) static int mtk_smi_larb_probe(struct platform_device *pdev)
{
	struct mtk_smi_larb *larb;
	struct resource *res;
	struct device *dev = &pdev->dev;
	struct device_node *smi_node;
	struct platform_device *smi_pdev;

	larb = devm_kzalloc(dev, sizeof(*larb), GFP_KERNEL);
	if (!larb)
		return -ENOMEM;

	larb->larb_gen = of_device_get_match_data(dev);
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	larb->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(larb->base))
		return PTR_ERR(larb->base);

	larb->smi.clk_apb = devm_clk_get(dev, "apb");
	if (IS_ERR(larb->smi.clk_apb))
		return PTR_ERR(larb->smi.clk_apb);

	larb->smi.clk_smi = devm_clk_get(dev, "smi");
	if (IS_ERR(larb->smi.clk_smi))
		return PTR_ERR(larb->smi.clk_smi);

	if (larb->larb_gen->has_gals) {
		/* The larbs may still haven't gals even if the SoC support.*/
		larb->smi.clk_gals0 = devm_clk_get(dev, "gals");
		if (PTR_ERR(larb->smi.clk_gals0) == -ENOENT)
			larb->smi.clk_gals0 = NULL;
		else if (IS_ERR(larb->smi.clk_gals0))
			return PTR_ERR(larb->smi.clk_gals0);
	}
	larb->smi.dev = dev;

	smi_node = of_parse_phandle(dev->of_node, "mediatek,smi", 0);
	if (!smi_node)
		return -EINVAL;

	smi_pdev = of_find_device_by_node(smi_node);
	of_node_put(smi_node);
	if (smi_pdev) {
		if (!platform_get_drvdata(smi_pdev))
			return -EPROBE_DEFER;
		larb->smi_common_dev = &smi_pdev->dev;
	} else {
		dev_err(dev, "Failed to get the smi_common device\n");
		return -EINVAL;
	}

	pm_runtime_enable(dev);
	platform_set_drvdata(pdev, larb);
	return component_add(dev, &mtk_smi_larb_component_ops);
}