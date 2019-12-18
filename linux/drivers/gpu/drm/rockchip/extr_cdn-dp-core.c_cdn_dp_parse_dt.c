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
struct platform_device {int dummy; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct cdn_dp_device {void* apb_rst; void* core_rst; void* dptx_rst; void* spdif_rst; void* grf_clk; void* spdif_clk; void* pclk; void* core_clk; void* regs; void* grf; struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_reset_control_get (struct device*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int cdn_dp_parse_dt(struct cdn_dp_device *dp)
{
	struct device *dev = dp->dev;
	struct device_node *np = dev->of_node;
	struct platform_device *pdev = to_platform_device(dev);
	struct resource *res;

	dp->grf = syscon_regmap_lookup_by_phandle(np, "rockchip,grf");
	if (IS_ERR(dp->grf)) {
		DRM_DEV_ERROR(dev, "cdn-dp needs rockchip,grf property\n");
		return PTR_ERR(dp->grf);
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	dp->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(dp->regs)) {
		DRM_DEV_ERROR(dev, "ioremap reg failed\n");
		return PTR_ERR(dp->regs);
	}

	dp->core_clk = devm_clk_get(dev, "core-clk");
	if (IS_ERR(dp->core_clk)) {
		DRM_DEV_ERROR(dev, "cannot get core_clk_dp\n");
		return PTR_ERR(dp->core_clk);
	}

	dp->pclk = devm_clk_get(dev, "pclk");
	if (IS_ERR(dp->pclk)) {
		DRM_DEV_ERROR(dev, "cannot get pclk\n");
		return PTR_ERR(dp->pclk);
	}

	dp->spdif_clk = devm_clk_get(dev, "spdif");
	if (IS_ERR(dp->spdif_clk)) {
		DRM_DEV_ERROR(dev, "cannot get spdif_clk\n");
		return PTR_ERR(dp->spdif_clk);
	}

	dp->grf_clk = devm_clk_get(dev, "grf");
	if (IS_ERR(dp->grf_clk)) {
		DRM_DEV_ERROR(dev, "cannot get grf clk\n");
		return PTR_ERR(dp->grf_clk);
	}

	dp->spdif_rst = devm_reset_control_get(dev, "spdif");
	if (IS_ERR(dp->spdif_rst)) {
		DRM_DEV_ERROR(dev, "no spdif reset control found\n");
		return PTR_ERR(dp->spdif_rst);
	}

	dp->dptx_rst = devm_reset_control_get(dev, "dptx");
	if (IS_ERR(dp->dptx_rst)) {
		DRM_DEV_ERROR(dev, "no uphy reset control found\n");
		return PTR_ERR(dp->dptx_rst);
	}

	dp->core_rst = devm_reset_control_get(dev, "core");
	if (IS_ERR(dp->core_rst)) {
		DRM_DEV_ERROR(dev, "no core reset control found\n");
		return PTR_ERR(dp->core_rst);
	}

	dp->apb_rst = devm_reset_control_get(dev, "apb");
	if (IS_ERR(dp->apb_rst)) {
		DRM_DEV_ERROR(dev, "no apb reset control found\n");
		return PTR_ERR(dp->apb_rst);
	}

	return 0;
}