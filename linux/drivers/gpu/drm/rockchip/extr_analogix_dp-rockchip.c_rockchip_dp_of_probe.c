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
struct rockchip_dp_device {int /*<<< orphan*/ * rst; int /*<<< orphan*/ * pclk; int /*<<< orphan*/ * grfclk; int /*<<< orphan*/ * grf; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*) ; 
 int ENOENT ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 void* devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_reset_control_get (struct device*,char*) ; 
 int /*<<< orphan*/ * syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int rockchip_dp_of_probe(struct rockchip_dp_device *dp)
{
	struct device *dev = dp->dev;
	struct device_node *np = dev->of_node;

	dp->grf = syscon_regmap_lookup_by_phandle(np, "rockchip,grf");
	if (IS_ERR(dp->grf)) {
		DRM_DEV_ERROR(dev, "failed to get rockchip,grf property\n");
		return PTR_ERR(dp->grf);
	}

	dp->grfclk = devm_clk_get(dev, "grf");
	if (PTR_ERR(dp->grfclk) == -ENOENT) {
		dp->grfclk = NULL;
	} else if (PTR_ERR(dp->grfclk) == -EPROBE_DEFER) {
		return -EPROBE_DEFER;
	} else if (IS_ERR(dp->grfclk)) {
		DRM_DEV_ERROR(dev, "failed to get grf clock\n");
		return PTR_ERR(dp->grfclk);
	}

	dp->pclk = devm_clk_get(dev, "pclk");
	if (IS_ERR(dp->pclk)) {
		DRM_DEV_ERROR(dev, "failed to get pclk property\n");
		return PTR_ERR(dp->pclk);
	}

	dp->rst = devm_reset_control_get(dev, "dp");
	if (IS_ERR(dp->rst)) {
		DRM_DEV_ERROR(dev, "failed to get dp reset control\n");
		return PTR_ERR(dp->rst);
	}

	return 0;
}