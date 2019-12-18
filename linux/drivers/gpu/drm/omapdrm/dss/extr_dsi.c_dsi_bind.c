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
typedef  int /*<<< orphan*/  u32 ;
struct dss_device {int dummy; } ;
struct TYPE_2__ {void* clks; void* irqs; void* regs; } ;
struct dsi_data {int module_id; TYPE_1__ debugfs; int /*<<< orphan*/  line_buffer_size; struct dss_device* dss; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_REVISION ; 
 int /*<<< orphan*/  FLD_GET (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dsi_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dsi_dump_dsi_clocks ; 
 int /*<<< orphan*/  dsi_dump_dsi_irqs ; 
 int /*<<< orphan*/  dsi_dump_dsi_regs ; 
 int /*<<< orphan*/  dsi_get_line_buf_size (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_init_pll_data (struct dss_device*,struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_read_reg (struct dsi_data*,int /*<<< orphan*/ ) ; 
 int dsi_runtime_get (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_runtime_put (struct dsi_data*) ; 
 void* dss_debugfs_create_file (struct dss_device*,char*,int /*<<< orphan*/ ,struct dsi_data*) ; 
 struct dss_device* dss_get_device (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int dsi_bind(struct device *dev, struct device *master, void *data)
{
	struct dss_device *dss = dss_get_device(master);
	struct dsi_data *dsi = dev_get_drvdata(dev);
	char name[10];
	u32 rev;
	int r;

	dsi->dss = dss;

	dsi_init_pll_data(dss, dsi);

	r = dsi_runtime_get(dsi);
	if (r)
		return r;

	rev = dsi_read_reg(dsi, DSI_REVISION);
	dev_dbg(dev, "OMAP DSI rev %d.%d\n",
	       FLD_GET(rev, 7, 4), FLD_GET(rev, 3, 0));

	dsi->line_buffer_size = dsi_get_line_buf_size(dsi);

	dsi_runtime_put(dsi);

	snprintf(name, sizeof(name), "dsi%u_regs", dsi->module_id + 1);
	dsi->debugfs.regs = dss_debugfs_create_file(dss, name,
						    dsi_dump_dsi_regs, dsi);
#ifdef CONFIG_OMAP2_DSS_COLLECT_IRQ_STATS
	snprintf(name, sizeof(name), "dsi%u_irqs", dsi->module_id + 1);
	dsi->debugfs.irqs = dss_debugfs_create_file(dss, name,
						    dsi_dump_dsi_irqs, dsi);
#endif
	snprintf(name, sizeof(name), "dsi%u_clks", dsi->module_id + 1);
	dsi->debugfs.clks = dss_debugfs_create_file(dss, name,
						    dsi_dump_dsi_clocks, dsi);

	return 0;
}