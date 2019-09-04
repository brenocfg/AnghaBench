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
struct drm_property {struct drm_device* dev; } ;
struct drm_mode_object {int type; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
#define  DRM_MODE_OBJECT_CONNECTOR 130 
#define  DRM_MODE_OBJECT_CRTC 129 
#define  DRM_MODE_OBJECT_PLANE 128 
 int EINVAL ; 
 int drm_connector_set_obj_prop (struct drm_mode_object*,struct drm_property*,int /*<<< orphan*/ ) ; 
 int drm_mode_crtc_set_obj_prop (struct drm_mode_object*,struct drm_property*,int /*<<< orphan*/ ) ; 
 int drm_mode_plane_set_obj_prop (int /*<<< orphan*/ ,struct drm_property*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_property_change_valid_get (struct drm_property*,int /*<<< orphan*/ ,struct drm_mode_object**) ; 
 int /*<<< orphan*/  drm_property_change_valid_put (struct drm_property*,struct drm_mode_object*) ; 
 int /*<<< orphan*/  obj_to_plane (struct drm_mode_object*) ; 

__attribute__((used)) static int set_property_legacy(struct drm_mode_object *obj,
			       struct drm_property *prop,
			       uint64_t prop_value)
{
	struct drm_device *dev = prop->dev;
	struct drm_mode_object *ref;
	int ret = -EINVAL;

	if (!drm_property_change_valid_get(prop, prop_value, &ref))
		return -EINVAL;

	drm_modeset_lock_all(dev);
	switch (obj->type) {
	case DRM_MODE_OBJECT_CONNECTOR:
		ret = drm_connector_set_obj_prop(obj, prop, prop_value);
		break;
	case DRM_MODE_OBJECT_CRTC:
		ret = drm_mode_crtc_set_obj_prop(obj, prop, prop_value);
		break;
	case DRM_MODE_OBJECT_PLANE:
		ret = drm_mode_plane_set_obj_prop(obj_to_plane(obj),
						  prop, prop_value);
		break;
	}
	drm_property_change_valid_put(prop, ref);
	drm_modeset_unlock_all(dev);

	return ret;
}