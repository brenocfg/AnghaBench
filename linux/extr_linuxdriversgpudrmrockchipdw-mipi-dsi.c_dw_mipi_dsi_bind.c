#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct reset_control {int dummy; } ;
struct platform_device {int dummy; } ;
struct of_device_id {struct dw_mipi_dsi_plat_data* data; } ;
struct dw_mipi_dsi_plat_data {int flags; } ;
struct TYPE_9__ {TYPE_2__* funcs; } ;
struct TYPE_10__ {TYPE_1__* funcs; } ;
struct TYPE_11__ {struct device* dev; int /*<<< orphan*/ * ops; } ;
struct dw_mipi_dsi {struct reset_control* pllref_clk; TYPE_3__ encoder; TYPE_4__ connector; TYPE_5__ dsi_host; int /*<<< orphan*/  panel; struct reset_control* grf_clk; struct reset_control* phy_cfg_clk; struct reset_control* pclk; struct reset_control* base; int /*<<< orphan*/  dpms_mode; struct dw_mipi_dsi_plat_data const* pdata; struct device* dev; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* destroy ) (TYPE_3__*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* destroy ) (TYPE_4__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,...) ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int DW_MIPI_NEEDS_GRF_CLK ; 
 int DW_MIPI_NEEDS_PHY_CFG_CLK ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct reset_control*) ; 
 int PTR_ERR (struct reset_control*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct reset_control*) ; 
 int clk_prepare_enable (struct reset_control*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct dw_mipi_dsi*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 struct reset_control* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct dw_mipi_dsi* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct reset_control* devm_reset_control_get (struct device*,char*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_dt_ids ; 
 int /*<<< orphan*/  dw_mipi_dsi_host_ops ; 
 int dw_mipi_dsi_register (struct drm_device*,struct dw_mipi_dsi*) ; 
 int mipi_dsi_host_register (TYPE_5__*) ; 
 int /*<<< orphan*/  mipi_dsi_host_unregister (TYPE_5__*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  reset_control_assert (struct reset_control*) ; 
 int /*<<< orphan*/  reset_control_deassert (struct reset_control*) ; 
 int rockchip_mipi_parse_dt (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int dw_mipi_dsi_bind(struct device *dev, struct device *master,
			    void *data)
{
	const struct of_device_id *of_id =
			of_match_device(dw_mipi_dsi_dt_ids, dev);
	const struct dw_mipi_dsi_plat_data *pdata = of_id->data;
	struct platform_device *pdev = to_platform_device(dev);
	struct reset_control *apb_rst;
	struct drm_device *drm = data;
	struct dw_mipi_dsi *dsi;
	struct resource *res;
	int ret;

	dsi = devm_kzalloc(dev, sizeof(*dsi), GFP_KERNEL);
	if (!dsi)
		return -ENOMEM;

	dsi->dev = dev;
	dsi->pdata = pdata;
	dsi->dpms_mode = DRM_MODE_DPMS_OFF;

	ret = rockchip_mipi_parse_dt(dsi);
	if (ret)
		return ret;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	dsi->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(dsi->base))
		return PTR_ERR(dsi->base);

	dsi->pllref_clk = devm_clk_get(dev, "ref");
	if (IS_ERR(dsi->pllref_clk)) {
		ret = PTR_ERR(dsi->pllref_clk);
		DRM_DEV_ERROR(dev,
			      "Unable to get pll reference clock: %d\n", ret);
		return ret;
	}

	dsi->pclk = devm_clk_get(dev, "pclk");
	if (IS_ERR(dsi->pclk)) {
		ret = PTR_ERR(dsi->pclk);
		DRM_DEV_ERROR(dev, "Unable to get pclk: %d\n", ret);
		return ret;
	}

	/*
	 * Note that the reset was not defined in the initial device tree, so
	 * we have to be prepared for it not being found.
	 */
	apb_rst = devm_reset_control_get(dev, "apb");
	if (IS_ERR(apb_rst)) {
		ret = PTR_ERR(apb_rst);
		if (ret == -ENOENT) {
			apb_rst = NULL;
		} else {
			DRM_DEV_ERROR(dev,
				      "Unable to get reset control: %d\n", ret);
			return ret;
		}
	}

	if (apb_rst) {
		ret = clk_prepare_enable(dsi->pclk);
		if (ret) {
			DRM_DEV_ERROR(dev, "Failed to enable pclk\n");
			return ret;
		}

		reset_control_assert(apb_rst);
		usleep_range(10, 20);
		reset_control_deassert(apb_rst);

		clk_disable_unprepare(dsi->pclk);
	}

	if (pdata->flags & DW_MIPI_NEEDS_PHY_CFG_CLK) {
		dsi->phy_cfg_clk = devm_clk_get(dev, "phy_cfg");
		if (IS_ERR(dsi->phy_cfg_clk)) {
			ret = PTR_ERR(dsi->phy_cfg_clk);
			DRM_DEV_ERROR(dev,
				      "Unable to get phy_cfg_clk: %d\n", ret);
			return ret;
		}
	}

	if (pdata->flags & DW_MIPI_NEEDS_GRF_CLK) {
		dsi->grf_clk = devm_clk_get(dev, "grf");
		if (IS_ERR(dsi->grf_clk)) {
			ret = PTR_ERR(dsi->grf_clk);
			DRM_DEV_ERROR(dev, "Unable to get grf_clk: %d\n", ret);
			return ret;
		}
	}

	ret = clk_prepare_enable(dsi->pllref_clk);
	if (ret) {
		DRM_DEV_ERROR(dev, "Failed to enable pllref_clk\n");
		return ret;
	}

	ret = dw_mipi_dsi_register(drm, dsi);
	if (ret) {
		DRM_DEV_ERROR(dev, "Failed to register mipi_dsi: %d\n", ret);
		goto err_pllref;
	}

	dsi->dsi_host.ops = &dw_mipi_dsi_host_ops;
	dsi->dsi_host.dev = dev;
	ret = mipi_dsi_host_register(&dsi->dsi_host);
	if (ret) {
		DRM_DEV_ERROR(dev, "Failed to register MIPI host: %d\n", ret);
		goto err_cleanup;
	}

	if (!dsi->panel) {
		ret = -EPROBE_DEFER;
		goto err_mipi_dsi_host;
	}

	dev_set_drvdata(dev, dsi);
	pm_runtime_enable(dev);
	return 0;

err_mipi_dsi_host:
	mipi_dsi_host_unregister(&dsi->dsi_host);
err_cleanup:
	dsi->connector.funcs->destroy(&dsi->connector);
	dsi->encoder.funcs->destroy(&dsi->encoder);
err_pllref:
	clk_disable_unprepare(dsi->pllref_clk);
	return ret;
}