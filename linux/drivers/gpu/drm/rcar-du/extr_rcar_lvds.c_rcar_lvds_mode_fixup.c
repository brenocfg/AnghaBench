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
struct rcar_lvds {TYPE_1__* info; } ;
struct drm_display_mode {int /*<<< orphan*/  clock; } ;
struct drm_bridge {int dummy; } ;
struct TYPE_2__ {int quirks; } ;

/* Variables and functions */
 int RCAR_LVDS_QUIRK_EXT_PLL ; 
 struct rcar_lvds* bridge_to_rcar_lvds (struct drm_bridge*) ; 
 int /*<<< orphan*/  clamp (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool rcar_lvds_mode_fixup(struct drm_bridge *bridge,
				 const struct drm_display_mode *mode,
				 struct drm_display_mode *adjusted_mode)
{
	struct rcar_lvds *lvds = bridge_to_rcar_lvds(bridge);
	int min_freq;

	/*
	 * The internal LVDS encoder has a restricted clock frequency operating
	 * range, from 5MHz to 148.5MHz on D3 and E3, and from 31MHz to
	 * 148.5MHz on all other platforms. Clamp the clock accordingly.
	 */
	min_freq = lvds->info->quirks & RCAR_LVDS_QUIRK_EXT_PLL ? 5000 : 31000;
	adjusted_mode->clock = clamp(adjusted_mode->clock, min_freq, 148500);

	return true;
}