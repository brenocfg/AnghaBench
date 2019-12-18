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
struct drm_plane {int dummy; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;

/* Variables and functions */
#define  DRM_PLANE_TYPE_CURSOR 130 
#define  DRM_PLANE_TYPE_OVERLAY 129 
#define  DRM_PLANE_TYPE_PRIMARY 128 
 int /*<<< orphan*/  drm_plane_create_zpos_immutable_property (struct drm_plane*,int) ; 
 int /*<<< orphan*/  drm_plane_create_zpos_property (struct drm_plane*,int,int /*<<< orphan*/ ,int) ; 
 int sti_plane_get_default_zpos (int) ; 

__attribute__((used)) static void sti_plane_attach_zorder_property(struct drm_plane *drm_plane,
					     enum drm_plane_type type)
{
	int zpos = sti_plane_get_default_zpos(type);

	switch (type) {
	case DRM_PLANE_TYPE_PRIMARY:
	case DRM_PLANE_TYPE_OVERLAY:
		drm_plane_create_zpos_property(drm_plane, zpos, 0, 6);
		break;
	case DRM_PLANE_TYPE_CURSOR:
		drm_plane_create_zpos_immutable_property(drm_plane, zpos);
		break;
	}
}