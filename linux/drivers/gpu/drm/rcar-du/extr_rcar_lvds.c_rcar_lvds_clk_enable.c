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
struct TYPE_4__ {int /*<<< orphan*/  mod; } ;
struct rcar_lvds {TYPE_2__ clocks; int /*<<< orphan*/  dev; TYPE_1__* info; } ;
struct drm_bridge {int dummy; } ;
struct TYPE_3__ {int quirks; } ;

/* Variables and functions */
 int ENODEV ; 
 int RCAR_LVDS_QUIRK_EXT_PLL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __rcar_lvds_pll_setup_d3_e3 (struct rcar_lvds*,unsigned long,int) ; 
 struct rcar_lvds* bridge_to_rcar_lvds (struct drm_bridge*) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long) ; 

int rcar_lvds_clk_enable(struct drm_bridge *bridge, unsigned long freq)
{
	struct rcar_lvds *lvds = bridge_to_rcar_lvds(bridge);
	int ret;

	if (WARN_ON(!(lvds->info->quirks & RCAR_LVDS_QUIRK_EXT_PLL)))
		return -ENODEV;

	dev_dbg(lvds->dev, "enabling LVDS PLL, freq=%luHz\n", freq);

	ret = clk_prepare_enable(lvds->clocks.mod);
	if (ret < 0)
		return ret;

	__rcar_lvds_pll_setup_d3_e3(lvds, freq, true);

	return 0;
}