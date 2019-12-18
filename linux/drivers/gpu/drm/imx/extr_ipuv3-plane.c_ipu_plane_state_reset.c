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
struct TYPE_2__ {unsigned int zpos; unsigned int normalized_zpos; } ;
struct ipu_plane_state {TYPE_1__ base; } ;
struct drm_plane {scalar_t__ type; int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 scalar_t__ DRM_PLANE_TYPE_PRIMARY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_destroy_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_reset (struct drm_plane*,TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct ipu_plane_state*) ; 
 struct ipu_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct ipu_plane_state* to_ipu_plane_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipu_plane_state_reset(struct drm_plane *plane)
{
	unsigned int zpos = (plane->type == DRM_PLANE_TYPE_PRIMARY) ? 0 : 1;
	struct ipu_plane_state *ipu_state;

	if (plane->state) {
		ipu_state = to_ipu_plane_state(plane->state);
		__drm_atomic_helper_plane_destroy_state(plane->state);
		kfree(ipu_state);
		plane->state = NULL;
	}

	ipu_state = kzalloc(sizeof(*ipu_state), GFP_KERNEL);

	if (ipu_state) {
		__drm_atomic_helper_plane_reset(plane, &ipu_state->base);
		ipu_state->base.zpos = zpos;
		ipu_state->base.normalized_zpos = zpos;
	}
}