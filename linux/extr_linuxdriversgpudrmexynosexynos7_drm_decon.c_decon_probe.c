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
struct resource {int /*<<< orphan*/  start; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct decon_context {int suspended; int i80_if; int /*<<< orphan*/  regs; void* encoder; int /*<<< orphan*/  wait_vsync_event; int /*<<< orphan*/  wait_vsync_queue; void* vclk; void* eclk; void* aclk; void* pclk; struct device* dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int component_add (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decon_component_ops ; 
 int /*<<< orphan*/  decon_irq_handler ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 struct decon_context* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct decon_context*) ; 
 void* exynos_dpi_probe (struct device*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_iomap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct decon_context*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 

__attribute__((used)) static int decon_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct decon_context *ctx;
	struct device_node *i80_if_timings;
	struct resource *res;
	int ret;

	if (!dev->of_node)
		return -ENODEV;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->dev = dev;
	ctx->suspended = true;

	i80_if_timings = of_get_child_by_name(dev->of_node, "i80-if-timings");
	if (i80_if_timings)
		ctx->i80_if = true;
	of_node_put(i80_if_timings);

	ctx->regs = of_iomap(dev->of_node, 0);
	if (!ctx->regs)
		return -ENOMEM;

	ctx->pclk = devm_clk_get(dev, "pclk_decon0");
	if (IS_ERR(ctx->pclk)) {
		dev_err(dev, "failed to get bus clock pclk\n");
		ret = PTR_ERR(ctx->pclk);
		goto err_iounmap;
	}

	ctx->aclk = devm_clk_get(dev, "aclk_decon0");
	if (IS_ERR(ctx->aclk)) {
		dev_err(dev, "failed to get bus clock aclk\n");
		ret = PTR_ERR(ctx->aclk);
		goto err_iounmap;
	}

	ctx->eclk = devm_clk_get(dev, "decon0_eclk");
	if (IS_ERR(ctx->eclk)) {
		dev_err(dev, "failed to get eclock\n");
		ret = PTR_ERR(ctx->eclk);
		goto err_iounmap;
	}

	ctx->vclk = devm_clk_get(dev, "decon0_vclk");
	if (IS_ERR(ctx->vclk)) {
		dev_err(dev, "failed to get vclock\n");
		ret = PTR_ERR(ctx->vclk);
		goto err_iounmap;
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_IRQ,
					   ctx->i80_if ? "lcd_sys" : "vsync");
	if (!res) {
		dev_err(dev, "irq request failed.\n");
		ret = -ENXIO;
		goto err_iounmap;
	}

	ret = devm_request_irq(dev, res->start, decon_irq_handler,
							0, "drm_decon", ctx);
	if (ret) {
		dev_err(dev, "irq request failed.\n");
		goto err_iounmap;
	}

	init_waitqueue_head(&ctx->wait_vsync_queue);
	atomic_set(&ctx->wait_vsync_event, 0);

	platform_set_drvdata(pdev, ctx);

	ctx->encoder = exynos_dpi_probe(dev);
	if (IS_ERR(ctx->encoder)) {
		ret = PTR_ERR(ctx->encoder);
		goto err_iounmap;
	}

	pm_runtime_enable(dev);

	ret = component_add(dev, &decon_component_ops);
	if (ret)
		goto err_disable_pm_runtime;

	return ret;

err_disable_pm_runtime:
	pm_runtime_disable(dev);

err_iounmap:
	iounmap(ctx->regs);

	return ret;
}