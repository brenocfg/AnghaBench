#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rockchip_dw_dsi_chip_data {scalar_t__ reg; int flags; int /*<<< orphan*/  max_data_lanes; } ;
struct resource {scalar_t__ start; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {struct dw_mipi_dsi_rockchip* priv_data; int /*<<< orphan*/ * host_ops; int /*<<< orphan*/ * phy_ops; int /*<<< orphan*/  max_data_lanes; void* base; } ;
struct dw_mipi_dsi_rockchip {void* pllref_clk; void* dmd; TYPE_1__ pdata; struct rockchip_dw_dsi_chip_data const* cdata; void* base; struct device* dev; void* grf_regmap; void* grf_clk; void* phy_cfg_clk; } ;
struct device_node {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,...) ; 
 int DW_MIPI_NEEDS_GRF_CLK ; 
 int DW_MIPI_NEEDS_PHY_CFG_CLK ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct dw_mipi_dsi_rockchip* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* dw_mipi_dsi_probe (struct platform_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_rockchip_host_ops ; 
 int /*<<< orphan*/  dw_mipi_dsi_rockchip_phy_ops ; 
 struct rockchip_dw_dsi_chip_data* of_device_get_match_data (struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dw_mipi_dsi_rockchip*) ; 
 void* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int dw_mipi_dsi_rockchip_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct dw_mipi_dsi_rockchip *dsi;
	struct resource *res;
	const struct rockchip_dw_dsi_chip_data *cdata =
				of_device_get_match_data(dev);
	int ret, i;

	dsi = devm_kzalloc(dev, sizeof(*dsi), GFP_KERNEL);
	if (!dsi)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	dsi->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(dsi->base)) {
		DRM_DEV_ERROR(dev, "Unable to get dsi registers\n");
		return PTR_ERR(dsi->base);
	}

	i = 0;
	while (cdata[i].reg) {
		if (cdata[i].reg == res->start) {
			dsi->cdata = &cdata[i];
			break;
		}

		i++;
	}

	if (!dsi->cdata) {
		dev_err(dev, "no dsi-config for %s node\n", np->name);
		return -EINVAL;
	}

	dsi->pllref_clk = devm_clk_get(dev, "ref");
	if (IS_ERR(dsi->pllref_clk)) {
		ret = PTR_ERR(dsi->pllref_clk);
		DRM_DEV_ERROR(dev,
			      "Unable to get pll reference clock: %d\n", ret);
		return ret;
	}

	if (dsi->cdata->flags & DW_MIPI_NEEDS_PHY_CFG_CLK) {
		dsi->phy_cfg_clk = devm_clk_get(dev, "phy_cfg");
		if (IS_ERR(dsi->phy_cfg_clk)) {
			ret = PTR_ERR(dsi->phy_cfg_clk);
			DRM_DEV_ERROR(dev,
				      "Unable to get phy_cfg_clk: %d\n", ret);
			return ret;
		}
	}

	if (dsi->cdata->flags & DW_MIPI_NEEDS_GRF_CLK) {
		dsi->grf_clk = devm_clk_get(dev, "grf");
		if (IS_ERR(dsi->grf_clk)) {
			ret = PTR_ERR(dsi->grf_clk);
			DRM_DEV_ERROR(dev, "Unable to get grf_clk: %d\n", ret);
			return ret;
		}
	}

	dsi->grf_regmap = syscon_regmap_lookup_by_phandle(np, "rockchip,grf");
	if (IS_ERR(dsi->grf_regmap)) {
		DRM_DEV_ERROR(dsi->dev, "Unable to get rockchip,grf\n");
		return PTR_ERR(dsi->grf_regmap);
	}

	dsi->dev = dev;
	dsi->pdata.base = dsi->base;
	dsi->pdata.max_data_lanes = dsi->cdata->max_data_lanes;
	dsi->pdata.phy_ops = &dw_mipi_dsi_rockchip_phy_ops;
	dsi->pdata.host_ops = &dw_mipi_dsi_rockchip_host_ops;
	dsi->pdata.priv_data = dsi;
	platform_set_drvdata(pdev, dsi);

	dsi->dmd = dw_mipi_dsi_probe(pdev, &dsi->pdata);
	if (IS_ERR(dsi->dmd)) {
		ret = PTR_ERR(dsi->dmd);
		if (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(dev,
				      "Failed to probe dw_mipi_dsi: %d\n", ret);
		goto err_clkdisable;
	}

	return 0;

err_clkdisable:
	clk_disable_unprepare(dsi->pllref_clk);
	return ret;
}