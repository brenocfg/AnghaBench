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
struct TYPE_2__ {int /*<<< orphan*/  regs; int /*<<< orphan*/  irqs; } ;
struct dsi_data {scalar_t__ scp_clk_refcount; int vdds_dsi_enabled; int /*<<< orphan*/ * vdds_dsi_reg; int /*<<< orphan*/  pll; TYPE_1__ debugfs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct dsi_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dsi_uninit_output (struct dsi_data*) ; 
 int /*<<< orphan*/  dss_debugfs_remove_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_pll_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_platform_depopulate (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dsi_unbind(struct device *dev, struct device *master, void *data)
{
	struct dsi_data *dsi = dev_get_drvdata(dev);

	dss_debugfs_remove_file(dsi->debugfs.irqs);
	dss_debugfs_remove_file(dsi->debugfs.regs);

	of_platform_depopulate(dev);

	WARN_ON(dsi->scp_clk_refcount > 0);

	dss_pll_unregister(&dsi->pll);

	dsi_uninit_output(dsi);

	pm_runtime_disable(dev);

	if (dsi->vdds_dsi_reg != NULL && dsi->vdds_dsi_enabled) {
		regulator_disable(dsi->vdds_dsi_reg);
		dsi->vdds_dsi_enabled = false;
	}
}