#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mod; } ;
struct rcar_lvds {TYPE_2__ clocks; TYPE_3__* companion; scalar_t__ dual_link; scalar_t__ panel; } ;
struct drm_bridge {int dummy; } ;
struct TYPE_6__ {TYPE_1__* funcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disable ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LVDCR0 ; 
 int /*<<< orphan*/  LVDCR1 ; 
 int /*<<< orphan*/  LVDPLLCR ; 
 struct rcar_lvds* bridge_to_rcar_lvds (struct drm_bridge*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_disable (scalar_t__) ; 
 int /*<<< orphan*/  drm_panel_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  rcar_lvds_write (struct rcar_lvds*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void rcar_lvds_disable(struct drm_bridge *bridge)
{
	struct rcar_lvds *lvds = bridge_to_rcar_lvds(bridge);

	if (lvds->panel) {
		drm_panel_disable(lvds->panel);
		drm_panel_unprepare(lvds->panel);
	}

	rcar_lvds_write(lvds, LVDCR0, 0);
	rcar_lvds_write(lvds, LVDCR1, 0);
	rcar_lvds_write(lvds, LVDPLLCR, 0);

	/* Disable the companion LVDS encoder in dual-link mode. */
	if (lvds->dual_link && lvds->companion)
		lvds->companion->funcs->disable(lvds->companion);

	clk_disable_unprepare(lvds->clocks.mod);
}