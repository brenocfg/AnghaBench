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
struct seq_file {int dummy; } ;
struct dispc_device {int /*<<< orphan*/  dss; } ;
typedef  enum dss_clk_source { ____Placeholder_dss_clk_source } dss_clk_source ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_DIVISOR ; 
 int /*<<< orphan*/  FEAT_CORE_CLK_DIV ; 
 int /*<<< orphan*/  FEAT_MGR_LCD2 ; 
 int /*<<< orphan*/  FEAT_MGR_LCD3 ; 
 int FLD_GET (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  OMAP_DSS_CHANNEL_LCD ; 
 int /*<<< orphan*/  OMAP_DSS_CHANNEL_LCD2 ; 
 int /*<<< orphan*/  OMAP_DSS_CHANNEL_LCD3 ; 
 int /*<<< orphan*/  dispc_dump_clocks_channel (struct dispc_device*,struct seq_file*,int /*<<< orphan*/ ) ; 
 int dispc_fclk_rate (struct dispc_device*) ; 
 scalar_t__ dispc_has_feature (struct dispc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_read_reg (struct dispc_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ dispc_runtime_get (struct dispc_device*) ; 
 int /*<<< orphan*/  dispc_runtime_put (struct dispc_device*) ; 
 int /*<<< orphan*/  dss_get_clk_source_name (int) ; 
 int dss_get_dispc_clk_source (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

void dispc_dump_clocks(struct dispc_device *dispc, struct seq_file *s)
{
	enum dss_clk_source dispc_clk_src;
	int lcd;
	u32 l;

	if (dispc_runtime_get(dispc))
		return;

	seq_printf(s, "- DISPC -\n");

	dispc_clk_src = dss_get_dispc_clk_source(dispc->dss);
	seq_printf(s, "dispc fclk source = %s\n",
			dss_get_clk_source_name(dispc_clk_src));

	seq_printf(s, "fck\t\t%-16lu\n", dispc_fclk_rate(dispc));

	if (dispc_has_feature(dispc, FEAT_CORE_CLK_DIV)) {
		seq_printf(s, "- DISPC-CORE-CLK -\n");
		l = dispc_read_reg(dispc, DISPC_DIVISOR);
		lcd = FLD_GET(l, 23, 16);

		seq_printf(s, "lck\t\t%-16lulck div\t%u\n",
				(dispc_fclk_rate(dispc)/lcd), lcd);
	}

	dispc_dump_clocks_channel(dispc, s, OMAP_DSS_CHANNEL_LCD);

	if (dispc_has_feature(dispc, FEAT_MGR_LCD2))
		dispc_dump_clocks_channel(dispc, s, OMAP_DSS_CHANNEL_LCD2);
	if (dispc_has_feature(dispc, FEAT_MGR_LCD3))
		dispc_dump_clocks_channel(dispc, s, OMAP_DSS_CHANNEL_LCD3);

	dispc_runtime_put(dispc);
}