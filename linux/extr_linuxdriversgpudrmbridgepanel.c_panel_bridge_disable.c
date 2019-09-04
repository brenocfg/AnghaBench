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
struct panel_bridge {int /*<<< orphan*/  panel; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 struct panel_bridge* drm_bridge_to_panel_bridge (struct drm_bridge*) ; 
 int /*<<< orphan*/  drm_panel_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void panel_bridge_disable(struct drm_bridge *bridge)
{
	struct panel_bridge *panel_bridge = drm_bridge_to_panel_bridge(bridge);

	drm_panel_disable(panel_bridge->panel);
}