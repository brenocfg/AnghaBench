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
typedef  int /*<<< orphan*/  uint64_t ;
struct drm_property {int flags; int /*<<< orphan*/  dev; } ;
struct drm_mode_object {TYPE_1__* properties; } ;
struct TYPE_2__ {int count; int /*<<< orphan*/ * values; struct drm_property** properties; } ;

/* Variables and functions */
 int DRM_MODE_PROP_IMMUTABLE ; 
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ drm_drv_uses_atomic_modeset (int /*<<< orphan*/ ) ; 

int drm_object_property_set_value(struct drm_mode_object *obj,
				  struct drm_property *property, uint64_t val)
{
	int i;

	WARN_ON(drm_drv_uses_atomic_modeset(property->dev) &&
		!(property->flags & DRM_MODE_PROP_IMMUTABLE));

	for (i = 0; i < obj->properties->count; i++) {
		if (obj->properties->properties[i] == property) {
			obj->properties->values[i] = val;
			return 0;
		}
	}

	return -EINVAL;
}