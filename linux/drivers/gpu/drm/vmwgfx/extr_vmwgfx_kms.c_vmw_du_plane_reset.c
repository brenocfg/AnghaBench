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
struct vmw_plane_state {int /*<<< orphan*/  base; } ;
struct drm_plane {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_reset (struct drm_plane*,int /*<<< orphan*/ *) ; 
 struct vmw_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_du_plane_destroy_state (struct drm_plane*,scalar_t__) ; 

void vmw_du_plane_reset(struct drm_plane *plane)
{
	struct vmw_plane_state *vps;


	if (plane->state)
		vmw_du_plane_destroy_state(plane, plane->state);

	vps = kzalloc(sizeof(*vps), GFP_KERNEL);

	if (!vps) {
		DRM_ERROR("Cannot allocate vmw_plane_state\n");
		return;
	}

	__drm_atomic_helper_plane_reset(plane, &vps->base);
}