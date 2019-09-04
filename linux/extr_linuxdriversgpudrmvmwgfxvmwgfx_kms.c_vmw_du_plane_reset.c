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
struct TYPE_2__ {int /*<<< orphan*/  rotation; struct drm_plane* plane; } ;
struct vmw_plane_state {TYPE_1__ base; } ;
struct drm_plane {TYPE_1__* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_ROTATE_0 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vmw_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_du_plane_destroy_state (struct drm_plane*,TYPE_1__*) ; 

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

	plane->state = &vps->base;
	plane->state->plane = plane;
	plane->state->rotation = DRM_MODE_ROTATE_0;
}