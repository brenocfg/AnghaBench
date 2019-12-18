#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  of_node; } ;
struct reset_control {TYPE_1__ dev; int /*<<< orphan*/  num_resources; int /*<<< orphan*/  resource; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  num_resources; int /*<<< orphan*/  resource; } ;
struct device_node {int dummy; } ;
struct clk {TYPE_1__ dev; int /*<<< orphan*/  num_resources; int /*<<< orphan*/  resource; } ;
struct TYPE_14__ {char* name; int flags; int /*<<< orphan*/  notify_event; int /*<<< orphan*/  capoffset; } ;
struct TYPE_16__ {int nr_resets; int /*<<< orphan*/  of_node; int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; } ;
struct ci_hdrc_msm {struct reset_control* core_clk; struct reset_control* iface_clk; struct reset_control* ci; TYPE_13__ pdata; int /*<<< orphan*/  hsic; struct reset_control* fs_clk; TYPE_5__ rcdev; struct reset_control* base; } ;

/* Variables and functions */
 int CI_HDRC_DISABLE_STREAMING ; 
 int CI_HDRC_OVERRIDE_AHB_BURST ; 
 int CI_HDRC_OVERRIDE_PHY_CONTROL ; 
 int CI_HDRC_REGS_SHARED ; 
 int /*<<< orphan*/  DEF_CAPOFFSET ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct reset_control*) ; 
 int PTR_ERR (struct reset_control*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct reset_control* ci_hdrc_add_device (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_13__*) ; 
 int ci_hdrc_msm_mux_phy (struct ci_hdrc_msm*,struct reset_control*) ; 
 int /*<<< orphan*/  ci_hdrc_msm_notify_event ; 
 int /*<<< orphan*/  ci_hdrc_msm_reset_ops ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct reset_control*) ; 
 int clk_prepare_enable (struct reset_control*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct reset_control* devm_clk_get (TYPE_1__*,char*) ; 
 struct reset_control* devm_clk_get_optional (TYPE_1__*,char*) ; 
 struct ci_hdrc_msm* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct reset_control* devm_platform_ioremap_resource (struct reset_control*,int) ; 
 struct reset_control* devm_reset_control_get (TYPE_1__*,char*) ; 
 int devm_reset_controller_register (TYPE_1__*,TYPE_5__*) ; 
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,char*) ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 struct device_node* of_get_next_available_child (struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct reset_control*,struct ci_hdrc_msm*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_no_callbacks (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_1__*) ; 
 int /*<<< orphan*/  reset_control_assert (struct reset_control*) ; 
 int /*<<< orphan*/  reset_control_deassert (struct reset_control*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ci_hdrc_msm_probe(struct platform_device *pdev)
{
	struct ci_hdrc_msm *ci;
	struct platform_device *plat_ci;
	struct clk *clk;
	struct reset_control *reset;
	int ret;
	struct device_node *ulpi_node, *phy_node;

	dev_dbg(&pdev->dev, "ci_hdrc_msm_probe\n");

	ci = devm_kzalloc(&pdev->dev, sizeof(*ci), GFP_KERNEL);
	if (!ci)
		return -ENOMEM;
	platform_set_drvdata(pdev, ci);

	ci->pdata.name = "ci_hdrc_msm";
	ci->pdata.capoffset = DEF_CAPOFFSET;
	ci->pdata.flags	= CI_HDRC_REGS_SHARED | CI_HDRC_DISABLE_STREAMING |
			  CI_HDRC_OVERRIDE_AHB_BURST |
			  CI_HDRC_OVERRIDE_PHY_CONTROL;
	ci->pdata.notify_event = ci_hdrc_msm_notify_event;

	reset = devm_reset_control_get(&pdev->dev, "core");
	if (IS_ERR(reset))
		return PTR_ERR(reset);

	ci->core_clk = clk = devm_clk_get(&pdev->dev, "core");
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	ci->iface_clk = clk = devm_clk_get(&pdev->dev, "iface");
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	ci->fs_clk = clk = devm_clk_get_optional(&pdev->dev, "fs");
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	ci->base = devm_platform_ioremap_resource(pdev, 1);
	if (IS_ERR(ci->base))
		return PTR_ERR(ci->base);

	ci->rcdev.owner = THIS_MODULE;
	ci->rcdev.ops = &ci_hdrc_msm_reset_ops;
	ci->rcdev.of_node = pdev->dev.of_node;
	ci->rcdev.nr_resets = 2;
	ret = devm_reset_controller_register(&pdev->dev, &ci->rcdev);
	if (ret)
		return ret;

	ret = clk_prepare_enable(ci->fs_clk);
	if (ret)
		return ret;

	reset_control_assert(reset);
	usleep_range(10000, 12000);
	reset_control_deassert(reset);

	clk_disable_unprepare(ci->fs_clk);

	ret = clk_prepare_enable(ci->core_clk);
	if (ret)
		return ret;

	ret = clk_prepare_enable(ci->iface_clk);
	if (ret)
		goto err_iface;

	ret = ci_hdrc_msm_mux_phy(ci, pdev);
	if (ret)
		goto err_mux;

	ulpi_node = of_get_child_by_name(pdev->dev.of_node, "ulpi");
	if (ulpi_node) {
		phy_node = of_get_next_available_child(ulpi_node, NULL);
		ci->hsic = of_device_is_compatible(phy_node, "qcom,usb-hsic-phy");
		of_node_put(phy_node);
	}
	of_node_put(ulpi_node);

	plat_ci = ci_hdrc_add_device(&pdev->dev, pdev->resource,
				     pdev->num_resources, &ci->pdata);
	if (IS_ERR(plat_ci)) {
		ret = PTR_ERR(plat_ci);
		if (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "ci_hdrc_add_device failed!\n");
		goto err_mux;
	}

	ci->ci = plat_ci;

	pm_runtime_set_active(&pdev->dev);
	pm_runtime_no_callbacks(&pdev->dev);
	pm_runtime_enable(&pdev->dev);

	return 0;

err_mux:
	clk_disable_unprepare(ci->iface_clk);
err_iface:
	clk_disable_unprepare(ci->core_clk);
	return ret;
}