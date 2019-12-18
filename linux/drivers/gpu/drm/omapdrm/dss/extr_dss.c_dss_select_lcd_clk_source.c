#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dss_device {int* lcd_clk_source; TYPE_2__* feat; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
typedef  enum dss_clk_source { ____Placeholder_dss_clk_source } dss_clk_source ;
struct TYPE_4__ {TYPE_1__* ops; int /*<<< orphan*/  has_lcd_clk_src; } ;
struct TYPE_3__ {int (* select_lcd_source ) (struct dss_device*,int,int) ;} ;

/* Variables and functions */
 int dss_get_channel_index (int) ; 
 int /*<<< orphan*/  dss_select_dispc_clk_source (struct dss_device*,int) ; 
 int stub1 (struct dss_device*,int,int) ; 

void dss_select_lcd_clk_source(struct dss_device *dss,
			       enum omap_channel channel,
			       enum dss_clk_source clk_src)
{
	int idx = dss_get_channel_index(channel);
	int r;

	if (!dss->feat->has_lcd_clk_src) {
		dss_select_dispc_clk_source(dss, clk_src);
		dss->lcd_clk_source[idx] = clk_src;
		return;
	}

	r = dss->feat->ops->select_lcd_source(dss, channel, clk_src);
	if (r)
		return;

	dss->lcd_clk_source[idx] = clk_src;
}