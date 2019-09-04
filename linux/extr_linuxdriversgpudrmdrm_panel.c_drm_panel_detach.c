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
struct drm_panel {int /*<<< orphan*/ * drm; int /*<<< orphan*/ * connector; } ;

/* Variables and functions */

int drm_panel_detach(struct drm_panel *panel)
{
	panel->connector = NULL;
	panel->drm = NULL;

	return 0;
}