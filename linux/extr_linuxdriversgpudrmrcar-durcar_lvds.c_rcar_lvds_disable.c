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
struct rcar_lvds {int enabled; int /*<<< orphan*/  clock; scalar_t__ panel; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LVDCR0 ; 
 int /*<<< orphan*/  LVDCR1 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct rcar_lvds* bridge_to_rcar_lvds (struct drm_bridge*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_disable (scalar_t__) ; 
 int /*<<< orphan*/  drm_panel_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  rcar_lvds_write (struct rcar_lvds*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcar_lvds_disable(struct drm_bridge *bridge)
{
	struct rcar_lvds *lvds = bridge_to_rcar_lvds(bridge);

	WARN_ON(!lvds->enabled);

	if (lvds->panel) {
		drm_panel_disable(lvds->panel);
		drm_panel_unprepare(lvds->panel);
	}

	rcar_lvds_write(lvds, LVDCR0, 0);
	rcar_lvds_write(lvds, LVDCR1, 0);

	clk_disable_unprepare(lvds->clock);

	lvds->enabled = false;
}