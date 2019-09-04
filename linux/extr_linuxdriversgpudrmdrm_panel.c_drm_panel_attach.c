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
struct drm_panel {int /*<<< orphan*/  drm; struct drm_connector* connector; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 

int drm_panel_attach(struct drm_panel *panel, struct drm_connector *connector)
{
	if (panel->connector)
		return -EBUSY;

	panel->connector = connector;
	panel->drm = connector->dev;

	return 0;
}