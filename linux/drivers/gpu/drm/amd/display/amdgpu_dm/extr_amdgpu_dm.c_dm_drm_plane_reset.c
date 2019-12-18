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
struct drm_plane {scalar_t__ state; TYPE_1__* funcs; } ;
struct dm_plane_state {int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* atomic_destroy_state ) (struct drm_plane*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_reset (struct drm_plane*,int /*<<< orphan*/ *) ; 
 struct dm_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct drm_plane*,scalar_t__) ; 

__attribute__((used)) static void dm_drm_plane_reset(struct drm_plane *plane)
{
	struct dm_plane_state *amdgpu_state = NULL;

	if (plane->state)
		plane->funcs->atomic_destroy_state(plane, plane->state);

	amdgpu_state = kzalloc(sizeof(*amdgpu_state), GFP_KERNEL);
	WARN_ON(amdgpu_state == NULL);

	if (amdgpu_state)
		__drm_atomic_helper_plane_reset(plane, &amdgpu_state->base);
}