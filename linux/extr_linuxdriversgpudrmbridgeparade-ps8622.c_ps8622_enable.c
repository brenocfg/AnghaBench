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
struct ps8622_bridge {int /*<<< orphan*/  panel; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 struct ps8622_bridge* bridge_to_ps8622 (struct drm_bridge*) ; 
 scalar_t__ drm_panel_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ps8622_enable(struct drm_bridge *bridge)
{
	struct ps8622_bridge *ps8622 = bridge_to_ps8622(bridge);

	if (drm_panel_enable(ps8622->panel)) {
		DRM_ERROR("failed to enable panel\n");
		return;
	}
}