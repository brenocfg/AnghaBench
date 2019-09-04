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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int skip_connector; struct drm_panel* panel; } ;
struct exynos_dp_device {struct drm_bridge* ptn_bridge; TYPE_1__ plat_data; } ;
struct drm_panel {int dummy; } ;
struct drm_bridge {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct drm_panel*) ; 
 int PTR_ERR (struct drm_panel*) ; 
 int component_add (struct device*,int /*<<< orphan*/ *) ; 
 struct exynos_dp_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int drm_of_find_panel_or_bridge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_panel**,struct drm_bridge**) ; 
 int /*<<< orphan*/  exynos_dp_ops ; 
 struct drm_panel* of_drm_find_panel (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct exynos_dp_device*) ; 

__attribute__((used)) static int exynos_dp_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np;
	struct exynos_dp_device *dp;
	struct drm_panel *panel;
	struct drm_bridge *bridge;
	int ret;

	dp = devm_kzalloc(&pdev->dev, sizeof(struct exynos_dp_device),
			  GFP_KERNEL);
	if (!dp)
		return -ENOMEM;

	/*
	 * We just use the drvdata until driver run into component
	 * add function, and then we would set drvdata to null, so
	 * that analogix dp driver would take charge of the drvdata.
	 */
	platform_set_drvdata(pdev, dp);

	/* This is for the backward compatibility. */
	np = of_parse_phandle(dev->of_node, "panel", 0);
	if (np) {
		dp->plat_data.panel = of_drm_find_panel(np);

		of_node_put(np);
		if (IS_ERR(dp->plat_data.panel))
			return PTR_ERR(dp->plat_data.panel);

		goto out;
	}

	ret = drm_of_find_panel_or_bridge(dev->of_node, 0, 0, &panel, &bridge);
	if (ret)
		return ret;

	/* The remote port can be either a panel or a bridge */
	dp->plat_data.panel = panel;
	dp->plat_data.skip_connector = !!bridge;
	dp->ptn_bridge = bridge;

out:
	return component_add(&pdev->dev, &exynos_dp_ops);
}