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
struct hdmi_phy_cfg {int num_regs; int num_clks; int /*<<< orphan*/ * clk_names; int /*<<< orphan*/ * reg_names; } ;
struct hdmi_phy {int /*<<< orphan*/ * clks; int /*<<< orphan*/ * regs; TYPE_1__* pdev; struct hdmi_phy_cfg* cfg; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

int msm_hdmi_phy_resource_enable(struct hdmi_phy *phy)
{
	struct hdmi_phy_cfg *cfg = phy->cfg;
	struct device *dev = &phy->pdev->dev;
	int i, ret = 0;

	pm_runtime_get_sync(dev);

	for (i = 0; i < cfg->num_regs; i++) {
		ret = regulator_enable(phy->regs[i]);
		if (ret)
			DRM_DEV_ERROR(dev, "failed to enable regulator: %s (%d)\n",
				cfg->reg_names[i], ret);
	}

	for (i = 0; i < cfg->num_clks; i++) {
		ret = clk_prepare_enable(phy->clks[i]);
		if (ret)
			DRM_DEV_ERROR(dev, "failed to enable clock: %s (%d)\n",
				cfg->clk_names[i], ret);
	}

	return ret;
}