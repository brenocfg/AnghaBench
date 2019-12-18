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
struct hdmi_phy_cfg {int num_clks; int num_regs; } ;
struct hdmi_phy {int /*<<< orphan*/ * regs; int /*<<< orphan*/ * clks; TYPE_1__* pdev; struct hdmi_phy_cfg* cfg; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

void msm_hdmi_phy_resource_disable(struct hdmi_phy *phy)
{
	struct hdmi_phy_cfg *cfg = phy->cfg;
	struct device *dev = &phy->pdev->dev;
	int i;

	for (i = cfg->num_clks - 1; i >= 0; i--)
		clk_disable_unprepare(phy->clks[i]);

	for (i = cfg->num_regs - 1; i >= 0; i--)
		regulator_disable(phy->regs[i]);

	pm_runtime_put_sync(dev);
}