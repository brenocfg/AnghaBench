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
struct innolux_panel {int enabled; int /*<<< orphan*/  backlight; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_disable (int /*<<< orphan*/ ) ; 
 struct innolux_panel* to_innolux_panel (struct drm_panel*) ; 

__attribute__((used)) static int innolux_panel_disable(struct drm_panel *panel)
{
	struct innolux_panel *innolux = to_innolux_panel(panel);

	if (!innolux->enabled)
		return 0;

	backlight_disable(innolux->backlight);

	innolux->enabled = false;

	return 0;
}