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
typedef  int u16 ;
struct dispc_device {int core_clk_rate; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DISPC_DIVISORo (int) ; 
 int /*<<< orphan*/  FEAT_CORE_CLK_DIV ; 
 int FLD_VAL (int,int,int) ; 
 int OMAP_DSS_CHANNEL_LCD ; 
 int dispc_fclk_rate (struct dispc_device*) ; 
 int /*<<< orphan*/  dispc_has_feature (struct dispc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_write_reg (struct dispc_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dispc_mgr_set_lcd_divisor(struct dispc_device *dispc,
				      enum omap_channel channel, u16 lck_div,
				      u16 pck_div)
{
	BUG_ON(lck_div < 1);
	BUG_ON(pck_div < 1);

	dispc_write_reg(dispc, DISPC_DIVISORo(channel),
			FLD_VAL(lck_div, 23, 16) | FLD_VAL(pck_div, 7, 0));

	if (!dispc_has_feature(dispc, FEAT_CORE_CLK_DIV) &&
			channel == OMAP_DSS_CHANNEL_LCD)
		dispc->core_clk_rate = dispc_fclk_rate(dispc) / lck_div;
}