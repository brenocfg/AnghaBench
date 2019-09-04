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
struct dss_device {int* lcd_clk_source; int dispc_clk_source; TYPE_1__* feat; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
typedef  enum dss_clk_source { ____Placeholder_dss_clk_source } dss_clk_source ;
struct TYPE_2__ {scalar_t__ has_lcd_clk_src; } ;

/* Variables and functions */
 int dss_get_channel_index (int) ; 

enum dss_clk_source dss_get_lcd_clk_source(struct dss_device *dss,
					   enum omap_channel channel)
{
	if (dss->feat->has_lcd_clk_src) {
		int idx = dss_get_channel_index(channel);
		return dss->lcd_clk_source[idx];
	} else {
		/* LCD_CLK source is the same as DISPC_FCLK source for
		 * OMAP2 and OMAP3 */
		return dss->dispc_clk_source;
	}
}