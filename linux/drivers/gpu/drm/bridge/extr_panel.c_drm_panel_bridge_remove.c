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
struct panel_bridge {TYPE_1__* panel; } ;
struct drm_bridge {int /*<<< orphan*/ * funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct drm_bridge*) ; 
 int /*<<< orphan*/  drm_bridge_remove (struct drm_bridge*) ; 
 struct panel_bridge* drm_bridge_to_panel_bridge (struct drm_bridge*) ; 
 int /*<<< orphan*/  panel_bridge_bridge_funcs ; 

void drm_panel_bridge_remove(struct drm_bridge *bridge)
{
	struct panel_bridge *panel_bridge;

	if (!bridge)
		return;

	if (bridge->funcs != &panel_bridge_bridge_funcs)
		return;

	panel_bridge = drm_bridge_to_panel_bridge(bridge);

	drm_bridge_remove(bridge);
	devm_kfree(panel_bridge->panel->dev, bridge);
}