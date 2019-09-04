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
struct qxl_device {int /*<<< orphan*/  ddev; scalar_t__ hotplug_mode_update_property; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_PROP_IMMUTABLE ; 
 scalar_t__ drm_property_create_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qxl_mode_create_hotplug_mode_update_property(struct qxl_device *qdev)
{
	if (qdev->hotplug_mode_update_property)
		return 0;

	qdev->hotplug_mode_update_property =
		drm_property_create_range(&qdev->ddev, DRM_MODE_PROP_IMMUTABLE,
					  "hotplug_mode_update", 0, 1);

	return 0;
}