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
struct seq_file {int dummy; } ;
typedef  enum omap_dss_clk_source { ____Placeholder_omap_dss_clk_source } omap_dss_clk_source ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dispc_mgr_get_lcd_divisor (int,int*,int*) ; 
 int /*<<< orphan*/  dispc_mgr_lclk_rate (int) ; 
 int /*<<< orphan*/  dispc_mgr_pclk_rate (int) ; 
 int /*<<< orphan*/  dss_feat_get_clk_source_name (int) ; 
 int /*<<< orphan*/  dss_get_generic_clk_source_name (int) ; 
 int dss_get_lcd_clk_source (int) ; 
 TYPE_1__* mgr_desc ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void dispc_dump_clocks_channel(struct seq_file *s, enum omap_channel channel)
{
	int lcd, pcd;
	enum omap_dss_clk_source lcd_clk_src;

	seq_printf(s, "- %s -\n", mgr_desc[channel].name);

	lcd_clk_src = dss_get_lcd_clk_source(channel);

	seq_printf(s, "%s clk source = %s (%s)\n", mgr_desc[channel].name,
		dss_get_generic_clk_source_name(lcd_clk_src),
		dss_feat_get_clk_source_name(lcd_clk_src));

	dispc_mgr_get_lcd_divisor(channel, &lcd, &pcd);

	seq_printf(s, "lck\t\t%-16lulck div\t%u\n",
		dispc_mgr_lclk_rate(channel), lcd);
	seq_printf(s, "pck\t\t%-16lupck div\t%u\n",
		dispc_mgr_pclk_rate(channel), pcd);
}