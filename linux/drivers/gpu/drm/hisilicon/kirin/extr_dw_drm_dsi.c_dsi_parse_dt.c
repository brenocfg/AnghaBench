#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_3__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct dw_dsi {int /*<<< orphan*/  bridge; struct dsi_hw_ctx* ctx; } ;
struct dsi_hw_ctx {int /*<<< orphan*/  base; int /*<<< orphan*/  pclk; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 int drm_of_find_panel_or_bridge (struct device_node*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsi_parse_dt(struct platform_device *pdev, struct dw_dsi *dsi)
{
	struct dsi_hw_ctx *ctx = dsi->ctx;
	struct device_node *np = pdev->dev.of_node;
	struct resource *res;
	int ret;

	/*
	 * Get the endpoint node. In our case, dsi has one output port1
	 * to which the external HDMI bridge is connected.
	 */
	ret = drm_of_find_panel_or_bridge(np, 1, 0, NULL, &dsi->bridge);
	if (ret)
		return ret;

	ctx->pclk = devm_clk_get(&pdev->dev, "pclk");
	if (IS_ERR(ctx->pclk)) {
		DRM_ERROR("failed to get pclk clock\n");
		return PTR_ERR(ctx->pclk);
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ctx->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(ctx->base)) {
		DRM_ERROR("failed to remap dsi io region\n");
		return PTR_ERR(ctx->base);
	}

	return 0;
}