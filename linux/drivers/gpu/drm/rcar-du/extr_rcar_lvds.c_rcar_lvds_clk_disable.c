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
 int /*<<< orphan*/  LVDPLLCR ; 
 int RCAR_LVDS_QUIRK_EXT_PLL ; 
 scalar_t__ WARN_ON (int) ; 
 struct rcar_lvds* bridge_to_rcar_lvds (struct drm_bridge*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rcar_lvds_write (struct rcar_lvds*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rcar_lvds_clk_disable(struct drm_bridge *bridge)
{
	struct rcar_lvds *lvds = bridge_to_rcar_lvds(bridge);

	if (WARN_ON(!(lvds->info->quirks & RCAR_LVDS_QUIRK_EXT_PLL)))
		return;

	dev_dbg(lvds->dev, "disabling LVDS PLL\n");

	rcar_lvds_write(lvds, LVDPLLCR, 0);

	clk_disable_unprepare(lvds->clocks.mod);
}