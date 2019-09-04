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
struct drm_display_mode {int dummy; } ;
struct rcar_lvds {struct drm_display_mode display_mode; int /*<<< orphan*/  enabled; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct rcar_lvds* bridge_to_rcar_lvds (struct drm_bridge*) ; 
 int /*<<< orphan*/  rcar_lvds_get_lvds_mode (struct rcar_lvds*) ; 

__attribute__((used)) static void rcar_lvds_mode_set(struct drm_bridge *bridge,
			       struct drm_display_mode *mode,
			       struct drm_display_mode *adjusted_mode)
{
	struct rcar_lvds *lvds = bridge_to_rcar_lvds(bridge);

	WARN_ON(lvds->enabled);

	lvds->display_mode = *adjusted_mode;

	rcar_lvds_get_lvds_mode(lvds);
}