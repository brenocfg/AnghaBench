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
struct regulator {int dummy; } ;
struct hdmi_phy_cfg {int num_regs; int num_clks; int /*<<< orphan*/ * clk_names; int /*<<< orphan*/ * reg_names; } ;
struct hdmi_phy {struct regulator** clks; TYPE_1__* pdev; struct regulator** regs; struct hdmi_phy_cfg* cfg; } ;
struct device {int dummy; } ;
typedef  struct regulator clk ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator*) ; 
 int PTR_ERR (struct regulator*) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct regulator* devm_regulator_get (struct device*,int /*<<< orphan*/ ) ; 
 struct regulator* msm_clk_get (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msm_hdmi_phy_resource_init(struct hdmi_phy *phy)
{
	struct hdmi_phy_cfg *cfg = phy->cfg;
	struct device *dev = &phy->pdev->dev;
	int i, ret;

	phy->regs = devm_kcalloc(dev, cfg->num_regs, sizeof(phy->regs[0]),
				 GFP_KERNEL);
	if (!phy->regs)
		return -ENOMEM;

	phy->clks = devm_kcalloc(dev, cfg->num_clks, sizeof(phy->clks[0]),
				 GFP_KERNEL);
	if (!phy->clks)
		return -ENOMEM;

	for (i = 0; i < cfg->num_regs; i++) {
		struct regulator *reg;

		reg = devm_regulator_get(dev, cfg->reg_names[i]);
		if (IS_ERR(reg)) {
			ret = PTR_ERR(reg);
			DRM_DEV_ERROR(dev, "failed to get phy regulator: %s (%d)\n",
				cfg->reg_names[i], ret);
			return ret;
		}

		phy->regs[i] = reg;
	}

	for (i = 0; i < cfg->num_clks; i++) {
		struct clk *clk;

		clk = msm_clk_get(phy->pdev, cfg->clk_names[i]);
		if (IS_ERR(clk)) {
			ret = PTR_ERR(clk);
			DRM_DEV_ERROR(dev, "failed to get phy clock: %s (%d)\n",
				cfg->clk_names[i], ret);
			return ret;
		}

		phy->clks[i] = clk;
	}

	return 0;
}