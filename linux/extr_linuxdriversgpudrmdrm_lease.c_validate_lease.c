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
struct drm_mode_object {scalar_t__ type; } ;
struct drm_file {scalar_t__ universal_planes; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DRM_MODE_OBJECT_CONNECTOR ; 
 scalar_t__ DRM_MODE_OBJECT_CRTC ; 
 scalar_t__ DRM_MODE_OBJECT_PLANE ; 
 int EINVAL ; 

__attribute__((used)) static int validate_lease(struct drm_device *dev,
			  struct drm_file *lessor_priv,
			  int object_count,
			  struct drm_mode_object **objects)
{
	int o;
	int has_crtc = -1;
	int has_connector = -1;
	int has_plane = -1;

	/* we want to confirm that there is at least one crtc, plane
	   connector object. */

	for (o = 0; o < object_count; o++) {
		if (objects[o]->type == DRM_MODE_OBJECT_CRTC && has_crtc == -1) {
			has_crtc = o;
		}
		if (objects[o]->type == DRM_MODE_OBJECT_CONNECTOR && has_connector == -1)
			has_connector = o;

		if (lessor_priv->universal_planes) {
			if (objects[o]->type == DRM_MODE_OBJECT_PLANE && has_plane == -1)
				has_plane = o;
		}
	}
	if (has_crtc == -1 || has_connector == -1)
		return -EINVAL;
	if (lessor_priv->universal_planes && has_plane == -1)
		return -EINVAL;
	return 0;
}