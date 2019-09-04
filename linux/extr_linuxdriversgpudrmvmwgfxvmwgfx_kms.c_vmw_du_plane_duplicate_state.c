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
struct drm_plane_state {int dummy; } ;
struct vmw_plane_state {struct drm_plane_state base; scalar_t__ bo; scalar_t__ surf; scalar_t__ cpp; scalar_t__ pinned; } ;
struct drm_plane {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_duplicate_state (struct drm_plane*,struct drm_plane_state*) ; 
 struct vmw_plane_state* kmemdup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_bo_reference (scalar_t__) ; 
 int /*<<< orphan*/  vmw_surface_reference (scalar_t__) ; 

struct drm_plane_state *
vmw_du_plane_duplicate_state(struct drm_plane *plane)
{
	struct drm_plane_state *state;
	struct vmw_plane_state *vps;

	vps = kmemdup(plane->state, sizeof(*vps), GFP_KERNEL);

	if (!vps)
		return NULL;

	vps->pinned = 0;
	vps->cpp = 0;

	/* Each ref counted resource needs to be acquired again */
	if (vps->surf)
		(void) vmw_surface_reference(vps->surf);

	if (vps->bo)
		(void) vmw_bo_reference(vps->bo);

	state = &vps->base;

	__drm_atomic_helper_plane_duplicate_state(plane, state);

	return state;
}