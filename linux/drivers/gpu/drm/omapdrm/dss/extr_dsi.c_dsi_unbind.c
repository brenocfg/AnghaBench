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
struct TYPE_2__ {int /*<<< orphan*/  regs; int /*<<< orphan*/  irqs; int /*<<< orphan*/  clks; } ;
struct dsi_data {scalar_t__ scp_clk_refcount; int /*<<< orphan*/  pll; TYPE_1__ debugfs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct dsi_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dss_debugfs_remove_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_pll_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dsi_unbind(struct device *dev, struct device *master, void *data)
{
	struct dsi_data *dsi = dev_get_drvdata(dev);

	dss_debugfs_remove_file(dsi->debugfs.clks);
	dss_debugfs_remove_file(dsi->debugfs.irqs);
	dss_debugfs_remove_file(dsi->debugfs.regs);

	WARN_ON(dsi->scp_clk_refcount > 0);

	dss_pll_unregister(&dsi->pll);
}