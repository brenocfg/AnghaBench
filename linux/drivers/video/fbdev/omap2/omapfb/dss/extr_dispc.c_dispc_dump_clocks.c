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
typedef  enum omap_dss_clk_source { ____Placeholder_omap_dss_clk_source } omap_dss_clk_source ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_DIVISOR ; 
 int /*<<< orphan*/  FEAT_CORE_CLK_DIV ; 
 int /*<<< orphan*/  FEAT_MGR_LCD2 ; 
 int /*<<< orphan*/  FEAT_MGR_LCD3 ; 
 int FLD_GET (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  OMAP_DSS_CHANNEL_LCD ; 
 int /*<<< orphan*/  OMAP_DSS_CHANNEL_LCD2 ; 
 int /*<<< orphan*/  OMAP_DSS_CHANNEL_LCD3 ; 
 int /*<<< orphan*/  dispc_dump_clocks_channel (struct seq_file*,int /*<<< orphan*/ ) ; 
 int dispc_fclk_rate () ; 
 int /*<<< orphan*/  dispc_read_reg (int /*<<< orphan*/ ) ; 
 scalar_t__ dispc_runtime_get () ; 
 int /*<<< orphan*/  dispc_runtime_put () ; 
 int dss_feat_get_clk_source_name (int) ; 
 int dss_get_dispc_clk_source () ; 
 int dss_get_generic_clk_source_name (int) ; 
 scalar_t__ dss_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

void dispc_dump_clocks(struct seq_file *s)
{
	int lcd;
	u32 l;
	enum omap_dss_clk_source dispc_clk_src = dss_get_dispc_clk_source();

	if (dispc_runtime_get())
		return;

	seq_printf(s, "- DISPC -\n");

	seq_printf(s, "dispc fclk source = %s (%s)\n",
			dss_get_generic_clk_source_name(dispc_clk_src),
			dss_feat_get_clk_source_name(dispc_clk_src));

	seq_printf(s, "fck\t\t%-16lu\n", dispc_fclk_rate());

	if (dss_has_feature(FEAT_CORE_CLK_DIV)) {
		seq_printf(s, "- DISPC-CORE-CLK -\n");
		l = dispc_read_reg(DISPC_DIVISOR);
		lcd = FLD_GET(l, 23, 16);

		seq_printf(s, "lck\t\t%-16lulck div\t%u\n",
				(dispc_fclk_rate()/lcd), lcd);
	}

	dispc_dump_clocks_channel(s, OMAP_DSS_CHANNEL_LCD);

	if (dss_has_feature(FEAT_MGR_LCD2))
		dispc_dump_clocks_channel(s, OMAP_DSS_CHANNEL_LCD2);
	if (dss_has_feature(FEAT_MGR_LCD3))
		dispc_dump_clocks_channel(s, OMAP_DSS_CHANNEL_LCD3);

	dispc_runtime_put();
}