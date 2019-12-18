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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_plane_funcs {int dummy; } ;
struct drm_plane {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;

/* Variables and functions */
 int DRM_PLANE_TYPE_OVERLAY ; 
 int DRM_PLANE_TYPE_PRIMARY ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,int /*<<< orphan*/ ,struct drm_plane_funcs const*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int drm_plane_init(struct drm_device *dev, struct drm_plane *plane,
		   uint32_t possible_crtcs,
		   const struct drm_plane_funcs *funcs,
		   const uint32_t *formats, unsigned int format_count,
		   bool is_primary)
{
	enum drm_plane_type type;

	type = is_primary ? DRM_PLANE_TYPE_PRIMARY : DRM_PLANE_TYPE_OVERLAY;
	return drm_universal_plane_init(dev, plane, possible_crtcs, funcs,
					formats, format_count,
					NULL, type, NULL);
}