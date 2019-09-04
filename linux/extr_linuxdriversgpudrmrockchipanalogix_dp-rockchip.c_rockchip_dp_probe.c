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
struct TYPE_2__ {struct drm_panel* panel; } ;
struct rockchip_dp_device {TYPE_1__ plat_data; int /*<<< orphan*/  adp; struct device* dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int component_add (struct device*,int /*<<< orphan*/ *) ; 
 struct rockchip_dp_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int drm_of_find_panel_or_bridge (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct drm_panel**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rockchip_dp_device*) ; 
 int /*<<< orphan*/  rockchip_dp_component_ops ; 
 int rockchip_dp_of_probe (struct rockchip_dp_device*) ; 

__attribute__((used)) static int rockchip_dp_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct drm_panel *panel = NULL;
	struct rockchip_dp_device *dp;
	int ret;

	ret = drm_of_find_panel_or_bridge(dev->of_node, 1, 0, &panel, NULL);
	if (ret < 0)
		return ret;

	dp = devm_kzalloc(dev, sizeof(*dp), GFP_KERNEL);
	if (!dp)
		return -ENOMEM;

	dp->dev = dev;
	dp->adp = ERR_PTR(-ENODEV);
	dp->plat_data.panel = panel;

	ret = rockchip_dp_of_probe(dp);
	if (ret < 0)
		return ret;

	platform_set_drvdata(pdev, dp);

	return component_add(dev, &rockchip_dp_component_ops);
}