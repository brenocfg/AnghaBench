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
typedef  int /*<<< orphan*/  u32 ;
struct dss_device {void** lcd_clk_source; void* dispc_clk_source; void** dsi_clk_source; int /*<<< orphan*/  dss_clk; int /*<<< orphan*/  dss_clk_rate; } ;

/* Variables and functions */
 void* DSS_CLK_SRC_FCK ; 
 int /*<<< orphan*/  DSS_CONTROL ; 
 int /*<<< orphan*/  DSS_REVISION ; 
 int /*<<< orphan*/  FLD_GET (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dss_device*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_read_reg (struct dss_device*,int /*<<< orphan*/ ) ; 
 int dss_runtime_get (struct dss_device*) ; 
 int /*<<< orphan*/  dss_runtime_put (struct dss_device*) ; 
 int /*<<< orphan*/  dss_select_dispc_clk_source (struct dss_device*,void*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dss_probe_hardware(struct dss_device *dss)
{
	u32 rev;
	int r;

	r = dss_runtime_get(dss);
	if (r)
		return r;

	dss->dss_clk_rate = clk_get_rate(dss->dss_clk);

	/* Select DPLL */
	REG_FLD_MOD(dss, DSS_CONTROL, 0, 0, 0);

	dss_select_dispc_clk_source(dss, DSS_CLK_SRC_FCK);

#ifdef CONFIG_OMAP2_DSS_VENC
	REG_FLD_MOD(dss, DSS_CONTROL, 1, 4, 4);	/* venc dac demen */
	REG_FLD_MOD(dss, DSS_CONTROL, 1, 3, 3);	/* venc clock 4x enable */
	REG_FLD_MOD(dss, DSS_CONTROL, 0, 2, 2);	/* venc clock mode = normal */
#endif
	dss->dsi_clk_source[0] = DSS_CLK_SRC_FCK;
	dss->dsi_clk_source[1] = DSS_CLK_SRC_FCK;
	dss->dispc_clk_source = DSS_CLK_SRC_FCK;
	dss->lcd_clk_source[0] = DSS_CLK_SRC_FCK;
	dss->lcd_clk_source[1] = DSS_CLK_SRC_FCK;

	rev = dss_read_reg(dss, DSS_REVISION);
	pr_info("OMAP DSS rev %d.%d\n", FLD_GET(rev, 7, 4), FLD_GET(rev, 3, 0));

	dss_runtime_put(dss);

	return 0;
}