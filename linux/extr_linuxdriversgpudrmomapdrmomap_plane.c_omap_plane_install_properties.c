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
struct omap_drm_private {scalar_t__ zorder_prop; scalar_t__ has_dmm; } ;
struct drm_mode_object {int dummy; } ;
struct drm_plane {scalar_t__ rotation_property; struct drm_mode_object base; struct drm_device* dev; } ;
struct drm_device {struct omap_drm_private* dev_private; } ;

/* Variables and functions */
 int DRM_MODE_REFLECT_X ; 
 int DRM_MODE_REFLECT_Y ; 
 int DRM_MODE_ROTATE_0 ; 
 int DRM_MODE_ROTATE_180 ; 
 int DRM_MODE_ROTATE_270 ; 
 int DRM_MODE_ROTATE_90 ; 
 int /*<<< orphan*/  drm_object_attach_property (struct drm_mode_object*,scalar_t__,int) ; 
 int /*<<< orphan*/  drm_plane_create_rotation_property (struct drm_plane*,int,int) ; 

void omap_plane_install_properties(struct drm_plane *plane,
		struct drm_mode_object *obj)
{
	struct drm_device *dev = plane->dev;
	struct omap_drm_private *priv = dev->dev_private;

	if (priv->has_dmm) {
		if (!plane->rotation_property)
			drm_plane_create_rotation_property(plane,
							   DRM_MODE_ROTATE_0,
							   DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_90 |
							   DRM_MODE_ROTATE_180 | DRM_MODE_ROTATE_270 |
							   DRM_MODE_REFLECT_X | DRM_MODE_REFLECT_Y);

		/* Attach the rotation property also to the crtc object */
		if (plane->rotation_property && obj != &plane->base)
			drm_object_attach_property(obj, plane->rotation_property,
						   DRM_MODE_ROTATE_0);
	}

	drm_object_attach_property(obj, priv->zorder_prop, 0);
}