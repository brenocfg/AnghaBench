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
struct drm_property {struct drm_device* dev; } ;
struct drm_plane {int /*<<< orphan*/  state; int /*<<< orphan*/  mutex; } ;
struct drm_mode_object {int type; } ;
struct TYPE_2__ {int /*<<< orphan*/  connection_mutex; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct drm_crtc {int /*<<< orphan*/  state; int /*<<< orphan*/  mutex; } ;
struct drm_connector {int /*<<< orphan*/  state; } ;

/* Variables and functions */
#define  DRM_MODE_OBJECT_CONNECTOR 130 
#define  DRM_MODE_OBJECT_CRTC 129 
#define  DRM_MODE_OBJECT_PLANE 128 
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int drm_atomic_connector_get_property (struct drm_connector*,int /*<<< orphan*/ ,struct drm_property*,int /*<<< orphan*/ *) ; 
 int drm_atomic_crtc_get_property (struct drm_crtc*,int /*<<< orphan*/ ,struct drm_property*,int /*<<< orphan*/ *) ; 
 int drm_atomic_plane_get_property (struct drm_plane*,int /*<<< orphan*/ ,struct drm_property*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_is_locked (int /*<<< orphan*/ *) ; 
 struct drm_connector* obj_to_connector (struct drm_mode_object*) ; 
 struct drm_crtc* obj_to_crtc (struct drm_mode_object*) ; 
 struct drm_plane* obj_to_plane (struct drm_mode_object*) ; 

int drm_atomic_get_property(struct drm_mode_object *obj,
		struct drm_property *property, uint64_t *val)
{
	struct drm_device *dev = property->dev;
	int ret;

	switch (obj->type) {
	case DRM_MODE_OBJECT_CONNECTOR: {
		struct drm_connector *connector = obj_to_connector(obj);
		WARN_ON(!drm_modeset_is_locked(&dev->mode_config.connection_mutex));
		ret = drm_atomic_connector_get_property(connector,
				connector->state, property, val);
		break;
	}
	case DRM_MODE_OBJECT_CRTC: {
		struct drm_crtc *crtc = obj_to_crtc(obj);
		WARN_ON(!drm_modeset_is_locked(&crtc->mutex));
		ret = drm_atomic_crtc_get_property(crtc,
				crtc->state, property, val);
		break;
	}
	case DRM_MODE_OBJECT_PLANE: {
		struct drm_plane *plane = obj_to_plane(obj);
		WARN_ON(!drm_modeset_is_locked(&plane->mutex));
		ret = drm_atomic_plane_get_property(plane,
				plane->state, property, val);
		break;
	}
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}