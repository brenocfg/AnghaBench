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
struct rcar_lvds {int dual_link; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 struct rcar_lvds* bridge_to_rcar_lvds (struct drm_bridge*) ; 

bool rcar_lvds_dual_link(struct drm_bridge *bridge)
{
	struct rcar_lvds *lvds = bridge_to_rcar_lvds(bridge);

	return lvds->dual_link;
}