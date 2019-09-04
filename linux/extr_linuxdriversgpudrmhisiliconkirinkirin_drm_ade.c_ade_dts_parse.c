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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct ade_hw_ctx {scalar_t__ irq; void* ade_pix_clk; void* media_noc_clk; void* ade_core_clk; void* noc_regmap; void* reset; void* base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_reset_control_get (struct device*,int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int ade_dts_parse(struct platform_device *pdev, struct ade_hw_ctx *ctx)
{
	struct resource *res;
	struct device *dev = &pdev->dev;
	struct device_node *np = pdev->dev.of_node;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ctx->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(ctx->base)) {
		DRM_ERROR("failed to remap ade io base\n");
		return  PTR_ERR(ctx->base);
	}

	ctx->reset = devm_reset_control_get(dev, NULL);
	if (IS_ERR(ctx->reset))
		return PTR_ERR(ctx->reset);

	ctx->noc_regmap =
		syscon_regmap_lookup_by_phandle(np, "hisilicon,noc-syscon");
	if (IS_ERR(ctx->noc_regmap)) {
		DRM_ERROR("failed to get noc regmap\n");
		return PTR_ERR(ctx->noc_regmap);
	}

	ctx->irq = platform_get_irq(pdev, 0);
	if (ctx->irq < 0) {
		DRM_ERROR("failed to get irq\n");
		return -ENODEV;
	}

	ctx->ade_core_clk = devm_clk_get(dev, "clk_ade_core");
	if (IS_ERR(ctx->ade_core_clk)) {
		DRM_ERROR("failed to parse clk ADE_CORE\n");
		return PTR_ERR(ctx->ade_core_clk);
	}

	ctx->media_noc_clk = devm_clk_get(dev, "clk_codec_jpeg");
	if (IS_ERR(ctx->media_noc_clk)) {
		DRM_ERROR("failed to parse clk CODEC_JPEG\n");
		return PTR_ERR(ctx->media_noc_clk);
	}

	ctx->ade_pix_clk = devm_clk_get(dev, "clk_ade_pix");
	if (IS_ERR(ctx->ade_pix_clk)) {
		DRM_ERROR("failed to parse clk ADE_PIX\n");
		return PTR_ERR(ctx->ade_pix_clk);
	}

	return 0;
}