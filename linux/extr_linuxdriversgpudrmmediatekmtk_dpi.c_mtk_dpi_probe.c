#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct mtk_dpi {int irq; int /*<<< orphan*/  ddp_comp; int /*<<< orphan*/  bridge; void* tvd_clk; void* pixel_clk; void* engine_clk; void* regs; struct device* dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MTK_DPI ; 
 int PTR_ERR (void*) ; 
 int component_add (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,struct device_node*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct mtk_dpi* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int mtk_ddp_comp_get_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mtk_ddp_comp_init (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_dpi_component_ops ; 
 int /*<<< orphan*/  mtk_dpi_funcs ; 
 int /*<<< orphan*/  of_drm_find_bridge (struct device_node*) ; 
 struct device_node* of_graph_get_remote_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_dpi*) ; 

__attribute__((used)) static int mtk_dpi_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct mtk_dpi *dpi;
	struct resource *mem;
	struct device_node *bridge_node;
	int comp_id;
	int ret;

	dpi = devm_kzalloc(dev, sizeof(*dpi), GFP_KERNEL);
	if (!dpi)
		return -ENOMEM;

	dpi->dev = dev;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	dpi->regs = devm_ioremap_resource(dev, mem);
	if (IS_ERR(dpi->regs)) {
		ret = PTR_ERR(dpi->regs);
		dev_err(dev, "Failed to ioremap mem resource: %d\n", ret);
		return ret;
	}

	dpi->engine_clk = devm_clk_get(dev, "engine");
	if (IS_ERR(dpi->engine_clk)) {
		ret = PTR_ERR(dpi->engine_clk);
		dev_err(dev, "Failed to get engine clock: %d\n", ret);
		return ret;
	}

	dpi->pixel_clk = devm_clk_get(dev, "pixel");
	if (IS_ERR(dpi->pixel_clk)) {
		ret = PTR_ERR(dpi->pixel_clk);
		dev_err(dev, "Failed to get pixel clock: %d\n", ret);
		return ret;
	}

	dpi->tvd_clk = devm_clk_get(dev, "pll");
	if (IS_ERR(dpi->tvd_clk)) {
		ret = PTR_ERR(dpi->tvd_clk);
		dev_err(dev, "Failed to get tvdpll clock: %d\n", ret);
		return ret;
	}

	dpi->irq = platform_get_irq(pdev, 0);
	if (dpi->irq <= 0) {
		dev_err(dev, "Failed to get irq: %d\n", dpi->irq);
		return -EINVAL;
	}

	bridge_node = of_graph_get_remote_node(dev->of_node, 0, 0);
	if (!bridge_node)
		return -ENODEV;

	dev_info(dev, "Found bridge node: %pOF\n", bridge_node);

	dpi->bridge = of_drm_find_bridge(bridge_node);
	of_node_put(bridge_node);
	if (!dpi->bridge)
		return -EPROBE_DEFER;

	comp_id = mtk_ddp_comp_get_id(dev->of_node, MTK_DPI);
	if (comp_id < 0) {
		dev_err(dev, "Failed to identify by alias: %d\n", comp_id);
		return comp_id;
	}

	ret = mtk_ddp_comp_init(dev, dev->of_node, &dpi->ddp_comp, comp_id,
				&mtk_dpi_funcs);
	if (ret) {
		dev_err(dev, "Failed to initialize component: %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, dpi);

	ret = component_add(dev, &mtk_dpi_component_ops);
	if (ret) {
		dev_err(dev, "Failed to add component: %d\n", ret);
		return ret;
	}

	return 0;
}