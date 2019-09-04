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
struct drm_property {int dummy; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {int dummy; } ;
struct drm_mode_object {int type; } ;
typedef  struct drm_plane_state drm_crtc_state ;
struct drm_crtc {int dummy; } ;
typedef  struct drm_plane_state drm_connector_state ;
struct drm_connector {int dummy; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
#define  DRM_MODE_OBJECT_CONNECTOR 130 
#define  DRM_MODE_OBJECT_CRTC 129 
#define  DRM_MODE_OBJECT_PLANE 128 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ERR (struct drm_plane_state*) ; 
 int PTR_ERR (struct drm_plane_state*) ; 
 int drm_atomic_connector_set_property (struct drm_connector*,struct drm_plane_state*,struct drm_property*,int /*<<< orphan*/ ) ; 
 int drm_atomic_crtc_set_property (struct drm_crtc*,struct drm_plane_state*,struct drm_property*,int /*<<< orphan*/ ) ; 
 struct drm_plane_state* drm_atomic_get_connector_state (struct drm_atomic_state*,struct drm_connector*) ; 
 struct drm_plane_state* drm_atomic_get_crtc_state (struct drm_atomic_state*,struct drm_crtc*) ; 
 struct drm_plane_state* drm_atomic_get_plane_state (struct drm_atomic_state*,struct drm_plane*) ; 
 int drm_atomic_plane_set_property (struct drm_plane*,struct drm_plane_state*,struct drm_property*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_property_change_valid_get (struct drm_property*,int /*<<< orphan*/ ,struct drm_mode_object**) ; 
 int /*<<< orphan*/  drm_property_change_valid_put (struct drm_property*,struct drm_mode_object*) ; 
 struct drm_connector* obj_to_connector (struct drm_mode_object*) ; 
 struct drm_crtc* obj_to_crtc (struct drm_mode_object*) ; 
 struct drm_plane* obj_to_plane (struct drm_mode_object*) ; 

int drm_atomic_set_property(struct drm_atomic_state *state,
			    struct drm_mode_object *obj,
			    struct drm_property *prop,
			    uint64_t prop_value)
{
	struct drm_mode_object *ref;
	int ret;

	if (!drm_property_change_valid_get(prop, prop_value, &ref))
		return -EINVAL;

	switch (obj->type) {
	case DRM_MODE_OBJECT_CONNECTOR: {
		struct drm_connector *connector = obj_to_connector(obj);
		struct drm_connector_state *connector_state;

		connector_state = drm_atomic_get_connector_state(state, connector);
		if (IS_ERR(connector_state)) {
			ret = PTR_ERR(connector_state);
			break;
		}

		ret = drm_atomic_connector_set_property(connector,
				connector_state, prop, prop_value);
		break;
	}
	case DRM_MODE_OBJECT_CRTC: {
		struct drm_crtc *crtc = obj_to_crtc(obj);
		struct drm_crtc_state *crtc_state;

		crtc_state = drm_atomic_get_crtc_state(state, crtc);
		if (IS_ERR(crtc_state)) {
			ret = PTR_ERR(crtc_state);
			break;
		}

		ret = drm_atomic_crtc_set_property(crtc,
				crtc_state, prop, prop_value);
		break;
	}
	case DRM_MODE_OBJECT_PLANE: {
		struct drm_plane *plane = obj_to_plane(obj);
		struct drm_plane_state *plane_state;

		plane_state = drm_atomic_get_plane_state(state, plane);
		if (IS_ERR(plane_state)) {
			ret = PTR_ERR(plane_state);
			break;
		}

		ret = drm_atomic_plane_set_property(plane,
				plane_state, prop, prop_value);
		break;
	}
	default:
		ret = -EINVAL;
		break;
	}

	drm_property_change_valid_put(prop, ref);
	return ret;
}