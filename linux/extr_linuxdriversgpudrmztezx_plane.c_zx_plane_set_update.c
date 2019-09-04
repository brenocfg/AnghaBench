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
struct zx_plane {int dummy; } ;
struct drm_plane {int type; TYPE_1__* state; } ;
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
#define  DRM_PLANE_TYPE_OVERLAY 129 
#define  DRM_PLANE_TYPE_PRIMARY 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 struct zx_plane* to_zx_plane (struct drm_plane*) ; 
 int /*<<< orphan*/  zx_gl_rsz_set_update (struct zx_plane*) ; 
 int /*<<< orphan*/  zx_gl_set_update (struct zx_plane*) ; 
 int /*<<< orphan*/  zx_vl_rsz_set_update (struct zx_plane*) ; 
 int /*<<< orphan*/  zx_vl_set_update (struct zx_plane*) ; 

void zx_plane_set_update(struct drm_plane *plane)
{
	struct zx_plane *zplane = to_zx_plane(plane);

	/* Do nothing if the plane is not enabled */
	if (!plane->state->crtc)
		return;

	switch (plane->type) {
	case DRM_PLANE_TYPE_PRIMARY:
		zx_gl_rsz_set_update(zplane);
		zx_gl_set_update(zplane);
		break;
	case DRM_PLANE_TYPE_OVERLAY:
		zx_vl_rsz_set_update(zplane);
		zx_vl_set_update(zplane);
		break;
	default:
		WARN_ONCE(1, "unsupported plane type %d\n", plane->type);
	}
}