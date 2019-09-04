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
typedef  int /*<<< orphan*/  uint64_t ;
struct drm_property {int /*<<< orphan*/  dev; } ;
struct drm_mode_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int __drm_object_property_get_value (struct drm_mode_object*,struct drm_property*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_drv_uses_atomic_modeset (int /*<<< orphan*/ ) ; 

int drm_object_property_get_value(struct drm_mode_object *obj,
				  struct drm_property *property, uint64_t *val)
{
	WARN_ON(drm_drv_uses_atomic_modeset(property->dev));

	return __drm_object_property_get_value(obj, property, val);
}