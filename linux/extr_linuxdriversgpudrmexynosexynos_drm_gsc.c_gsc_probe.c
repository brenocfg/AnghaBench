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
struct device {int dummy; } ;
struct platform_device {int /*<<< orphan*/  id; struct device dev; } ;
struct gsc_driverdata {int num_clocks; int /*<<< orphan*/  num_limits; int /*<<< orphan*/  limits; int /*<<< orphan*/ * clk_names; } ;
struct gsc_context {int num_clocks; int num_formats; int /*<<< orphan*/  id; int /*<<< orphan*/  irq; int /*<<< orphan*/  regs; void* regs_res; int /*<<< orphan*/ * clocks; int /*<<< orphan*/ * clk_names; struct exynos_drm_ipp_formats* formats; struct device* dev; } ;
struct exynos_drm_ipp_formats {int type; int /*<<< orphan*/  num_limits; int /*<<< orphan*/  limits; int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int DRM_EXYNOS_IPP_FORMAT_DESTINATION ; 
 int DRM_EXYNOS_IPP_FORMAT_SOURCE ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GSC_AUTOSUSPEND_DELAY ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int component_add (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,void*) ; 
 struct exynos_drm_ipp_formats* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct gsc_context* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gsc_context*) ; 
 int /*<<< orphan*/  gsc_component_ops ; 
 int /*<<< orphan*/ * gsc_formats ; 
 int /*<<< orphan*/  gsc_irq_handler ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 
 void* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct gsc_context*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 

__attribute__((used)) static int gsc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct gsc_driverdata *driver_data;
	struct exynos_drm_ipp_formats *formats;
	struct gsc_context *ctx;
	struct resource *res;
	int ret, i;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	formats = devm_kcalloc(dev,
			       ARRAY_SIZE(gsc_formats), sizeof(*formats),
			       GFP_KERNEL);
	if (!formats)
		return -ENOMEM;

	driver_data = (struct gsc_driverdata *)of_device_get_match_data(dev);
	ctx->dev = dev;
	ctx->num_clocks = driver_data->num_clocks;
	ctx->clk_names = driver_data->clk_names;

	for (i = 0; i < ARRAY_SIZE(gsc_formats); i++) {
		formats[i].fourcc = gsc_formats[i];
		formats[i].type = DRM_EXYNOS_IPP_FORMAT_SOURCE |
				  DRM_EXYNOS_IPP_FORMAT_DESTINATION;
		formats[i].limits = driver_data->limits;
		formats[i].num_limits = driver_data->num_limits;
	}
	ctx->formats = formats;
	ctx->num_formats = ARRAY_SIZE(gsc_formats);

	/* clock control */
	for (i = 0; i < ctx->num_clocks; i++) {
		ctx->clocks[i] = devm_clk_get(dev, ctx->clk_names[i]);
		if (IS_ERR(ctx->clocks[i])) {
			dev_err(dev, "failed to get clock: %s\n",
				ctx->clk_names[i]);
			return PTR_ERR(ctx->clocks[i]);
		}
	}

	/* resource memory */
	ctx->regs_res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ctx->regs = devm_ioremap_resource(dev, ctx->regs_res);
	if (IS_ERR(ctx->regs))
		return PTR_ERR(ctx->regs);

	/* resource irq */
	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res) {
		dev_err(dev, "failed to request irq resource.\n");
		return -ENOENT;
	}

	ctx->irq = res->start;
	ret = devm_request_irq(dev, ctx->irq, gsc_irq_handler, 0,
			       dev_name(dev), ctx);
	if (ret < 0) {
		dev_err(dev, "failed to request irq.\n");
		return ret;
	}

	/* context initailization */
	ctx->id = pdev->id;

	platform_set_drvdata(pdev, ctx);

	pm_runtime_use_autosuspend(dev);
	pm_runtime_set_autosuspend_delay(dev, GSC_AUTOSUSPEND_DELAY);
	pm_runtime_enable(dev);

	ret = component_add(dev, &gsc_component_ops);
	if (ret)
		goto err_pm_dis;

	dev_info(dev, "drm gsc registered successfully.\n");

	return 0;

err_pm_dis:
	pm_runtime_dont_use_autosuspend(dev);
	pm_runtime_disable(dev);
	return ret;
}