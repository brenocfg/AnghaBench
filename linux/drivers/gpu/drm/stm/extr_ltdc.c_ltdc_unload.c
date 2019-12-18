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
struct drm_device {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int MAX_ENDPOINTS ; 
 int /*<<< orphan*/  drm_of_panel_bridge_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 

void ltdc_unload(struct drm_device *ddev)
{
	int i;

	DRM_DEBUG_DRIVER("\n");

	for (i = 0; i < MAX_ENDPOINTS; i++)
		drm_of_panel_bridge_remove(ddev->dev->of_node, 0, i);

	pm_runtime_disable(ddev->dev);
}