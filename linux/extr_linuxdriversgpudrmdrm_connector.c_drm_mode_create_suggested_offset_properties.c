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
struct TYPE_2__ {int /*<<< orphan*/ * suggested_y_property; int /*<<< orphan*/ * suggested_x_property; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_PROP_IMMUTABLE ; 
 int ENOMEM ; 
 void* drm_property_create_range (struct drm_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

int drm_mode_create_suggested_offset_properties(struct drm_device *dev)
{
	if (dev->mode_config.suggested_x_property && dev->mode_config.suggested_y_property)
		return 0;

	dev->mode_config.suggested_x_property =
		drm_property_create_range(dev, DRM_MODE_PROP_IMMUTABLE, "suggested X", 0, 0xffffffff);

	dev->mode_config.suggested_y_property =
		drm_property_create_range(dev, DRM_MODE_PROP_IMMUTABLE, "suggested Y", 0, 0xffffffff);

	if (dev->mode_config.suggested_x_property == NULL ||
	    dev->mode_config.suggested_y_property == NULL)
		return -ENOMEM;
	return 0;
}